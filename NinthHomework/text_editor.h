#ifndef _TEXT_EDITOR_H
#define _TEXT_EDITOR_H

#include <sys/ioctl.h>
#include <signal.h>
#include <stdlib.h>
#include <ncurses.h>
#include <malloc.h>
#include "input.h"
#include <stdio.h>

#define MAX_DOC_SIZE 20971520

void edit_text_file(char * file_name);

#endif //_TEXT_EDITOR_H
