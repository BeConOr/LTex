#ifndef MY_BASH_H
#define MY_BASH_H

#include <termios.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <stdlib.h>
#include <ncurses.h>
#include <malloc.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>

struct windows_list{
    struct windows_list * next;
    struct windows_list * previous;
    WINDOW * value;
};

struct dir_list{
    struct dir_list * next;
    struct  dir_list * previous;
    struct dirent * value;
};

#endif //MY_BASH_H
