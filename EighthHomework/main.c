#include <termios.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <stdlib.h>
#include <ncurses.h>
#include <malloc.h>
#include "input.h"

#define MAX_DOC_SIZE 20971520
#define WINDOW_WIDTH 120
#define TEXT_STRING 20
#define COMMAND_STRING 1

void sig_winch(int signo);

int main(void)
{
	WINDOW * wnd;
	WINDOW * text_wnd;
    WINDOW * command_wnd;
	
	char * text = (char *) malloc(MAX_DOC_SIZE * sizeof(char));
	
	initscr();
	signal(SIGWINCH, sig_winch);
	cbreak();
	curs_set(0);
	start_color();
	refresh();
	wnd = newwin(TEXT_STRING + COMMAND_STRING + 5, WINDOW_WIDTH, 10, 4);
    keypad(wnd, 1);
	box(wnd, '|', '-');
    text_wnd = derwin(wnd, TEXT_STRING, WINDOW_WIDTH, 0, 0);
    command_wnd = derwin(wnd, COMMAND_STRING+2, WINDOW_WIDTH, TEXT_STRING+2, 0);
    box(text_wnd, '*', '*');
    box(command_wnd, '+', '+');
    refresh();
    input_text(&text_wnd, &command_wnd, WINDOW_WIDTH, text, MAX_DOC_SIZE);
    free(text);
	delwin(text_wnd);
	delwin(command_wnd);
	delwin(wnd);
	endwin();
	exit(EXIT_SUCCESS);
}

void sig_winch(int signo){
	struct winsize size;
	ioctl(fileno(stdout), TIOCGWINSZ, (char *) &size);
	resizeterm(size.ws_row, size.ws_col);
}