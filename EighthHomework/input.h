#ifndef _INPUT_H_
#define _INPUT_H_
#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>

struct INPUT_WINDOWS{
    WINDOW * main_window;
    WINDOW * text_window;
    WINDOW * command_window;
    int max_text_window_size;
};

struct TEXT{
    char * content;
    size_t text_length;
};

void input_text(WINDOW ** text_window, WINDOW ** command_window, int max_text_window_size, struct TEXT * text, size_t max_len, char * file);
int input_command(WINDOW ** win, char * text, char * name);

#endif
