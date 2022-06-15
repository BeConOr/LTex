#ifndef _INPUT_H_
#define _INPUT_H_
#include <curses.h>
#include <stdlib.h>

void input_text(WINDOW * win, char * text, size_t max_len);
int input_command(WINDOW * win, char * text, size_t max_len);

#endif
