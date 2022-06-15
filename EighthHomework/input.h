#ifndef _INPUT_H_
#define _INPUT_H_
#include <curses.h>
#include <stdlib.h>

struct INPUT_WINDOWS{
    WINDOW * text_window;
    WINDOW * command_window;
    int max_text_window_size;
};

void input_text(struct INPUT_WINDOWS wins, char * text, size_t max_len);
int input_command(WINDOW * win, char * text, size_t max_len);

#endif
