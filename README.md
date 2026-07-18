# Unix-LS-Command-Implementation
A C-based implementation of the Linux 'ls' command using POSIX system calls. This project supports options such as '-a', '-l', '-i', '-s', '-t', and '-r', with support for combined flags. It demonstrates directory traversal, file metadata retrieval, sorting, and command-line argument parsing using standard Linux APIs and system programming concepts.

## 📌 Project Overview

The objective of this project is to recreate the basic functionality of the Linux `ls` command for educational purposes. It provides hands-on experience with Linux system programming concepts such as directory traversal, file metadata retrieval, command-line argument parsing, and sorting.

The implementation supports several commonly used `ls` options and allows them to be combined, similar to the original Linux utility.

---

## ✨ Features

* List files and directories
* Display hidden files (`-a`)
* Long listing format (`-l`)
* Show inode numbers (`-i`)
* Show allocated file blocks (`-s`)
* Sort files by last modification time (`-t`)
* Reverse sorting order (`-r`)
* Support multiple options together (e.g., `-altr`)
* Error handling for invalid paths and permission issues

---

## 🛠 Technologies Used

* C Programming
* GCC Compiler
* Linux Operating System
* POSIX System Calls

---

## 📚 Libraries Used

```c
stdio.h
stdlib.h
string.h
dirent.h
sys/stat.h
pwd.h
grp.h
unistd.h
time.h
errno.h
```

## 📖 Supported Options

| Option | Description                   |
| ------ | ----------------------------- |
| `-a`   | Display hidden files          |
| `-l`   | Long listing format           |
| `-i`   | Display inode numbers         |
| `-s`   | Display allocated file blocks |
| `-t`   | Sort by modification time     |
| `-r`   | Reverse sorting order         |

---
## 🔧 System Calls Used

* `opendir()`
* `readdir()`
* `closedir()`
* `stat()`
* `lstat()`
* `getpwuid()`
* `getgrgid()`
* `strftime()`
* `qsort()`

---

