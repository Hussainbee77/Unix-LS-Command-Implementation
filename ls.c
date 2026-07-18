#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

int flag_a=0, flag_l=0, flag_i=0, flag_s=0, flag_t=0, flag_r=0;

int compare_alpha(const void *a, const void *b)
{
    struct dirent *d1=*(struct dirent **)a;
    struct dirent *d2=*(struct dirent **)b;
    return strcmp(d1->d_name,d2->d_name);
}

int compare_time(const void *a,const void *b)
{
    struct dirent *d1=*(struct dirent **)a;
    struct dirent *d2=*(struct dirent **)b;

    struct stat st1,st2;

    stat(d1->d_name,&st1);
    stat(d2->d_name,&st2);

    if(st1.st_mtime < st2.st_mtime)
        return 1;
    if(st1.st_mtime > st2.st_mtime)
        return -1;
    return 0;
}

void permissions(mode_t mode)
{
    printf((S_ISDIR(mode)) ? "d" : "-");
    printf((mode&S_IRUSR)?"r":"-");
    printf((mode&S_IWUSR)?"w":"-");
    printf((mode&S_IXUSR)?"x":"-");
    printf((mode&S_IRGRP)?"r":"-");
    printf((mode&S_IWGRP)?"w":"-");
    printf((mode&S_IXGRP)?"x":"-");
    printf((mode&S_IROTH)?"r":"-");
    printf((mode&S_IWOTH)?"w":"-");
    printf((mode&S_IXOTH)?"x":"-");
}

int main(int argc,char *argv[])
{
    int i;

    for(i=1;i<argc;i++)
    {
        if(argv[i][0]=='-')
        {
            int j;
            for(j=1;argv[i][j]!='\0';j++)
            {
                switch(argv[i][j])
                {
                    case 'a': flag_a=1; break;
                    case 'l': flag_l=1; break;
                    case 'i': flag_i=1; break;
                    case 's': flag_s=1; break;
                    case 't': flag_t=1; break;
                    case 'r': flag_r=1; break;
                }
            }
        }
    }

    DIR *dir=opendir(".");
    if(dir==NULL)
    {
        perror("opendir");
        return 1;
    }

    struct dirent *entry;
    struct dirent **list=NULL;
    int count=0;

    while((entry=readdir(dir))!=NULL)
    {
        if(!flag_a && entry->d_name[0]=='.')
            continue;

        list=realloc(list,(count+1)*sizeof(struct dirent *));
        list[count]=malloc(sizeof(struct dirent));
        memcpy(list[count],entry,sizeof(struct dirent));
        count++;
    }

    closedir(dir);

    if(flag_t)
        qsort(list,count,sizeof(struct dirent *),compare_time);
    else
        qsort(list,count,sizeof(struct dirent *),compare_alpha);

    if(flag_r)
    {
        for(i=count-1;i>=0;i--)
        {
            struct stat st;
            stat(list[i]->d_name,&st);

            if(flag_i)
                printf("%8lu ",(unsigned long)st.st_ino);

            if(flag_s)
                printf("%4ld ",st.st_blocks);

            if(flag_l)
            {
                permissions(st.st_mode);
                printf(" %2ld",st.st_nlink);
                printf(" %s",getpwuid(st.st_uid)->pw_name);
                printf(" %s",getgrgid(st.st_gid)->gr_name);
                printf(" %8ld",st.st_size);
                printf(" %.12s",ctime(&st.st_mtime));
            }

            printf(" %s\n",list[i]->d_name);
        }
    }
    else
    {
        for(i=0;i<count;i++)
        {
            struct stat st;
            stat(list[i]->d_name,&st);

            if(flag_i)
                printf("%8lu ",(unsigned long)st.st_ino);

            if(flag_s)
                printf("%4ld ",st.st_blocks);

            if(flag_l)
            {
                permissions(st.st_mode);
                printf(" %2ld",st.st_nlink);
                printf(" %s",getpwuid(st.st_uid)->pw_name);
                printf(" %s",getgrgid(st.st_gid)->gr_name);
                printf(" %8ld",st.st_size);
                printf(" %.12s",ctime(&st.st_mtime));
            }

            printf(" %s\n",list[i]->d_name);
        }
    }

    for(i=0;i<count;i++)
        free(list[i]);
    free(list);

    return 0;
}
