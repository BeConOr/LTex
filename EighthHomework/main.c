#include <termios.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <stdlib.h>
#include <curses.h>
#include <malloc.h>
#include "input.h"

#define MAX_DOC_SIZE 20971520
#define WINDOW_WIDTH 120

void sig_winch(int signo);

int main(void)
{
	WINDOW * wnd;
	WINDOW * text_wnd;
    WINDOW * command_wnd;
    struct INPUT_WINDOWS windows = {text_wnd, command_wnd, WINDOW_WIDTH};
	
	char * text = (char *) malloc(MAX_DOC_SIZE * sizeof(char));
	
	initscr();
	signal(SIGWINCH, sig_winch);
	cbreak();
	curs_set(0);
	start_color();
	refresh();
	wnd = newwin(120, 120, 2, 4);
    keypad(wnd, 1);
	box(wnd, '|', '-');
    text_wnd = derwin(wnd, 100, WINDOW_WIDTH, 0, 0);
    command_wnd = derwin(wnd, 20, WINDOW_WIDTH, 100, 0);
	wrefresh(wnd);
    input_text(windows, text, MAX_DOC_SIZE);
    free(text);
	delwin(subwnd);
	delwin(wnd);
	endwin();
	exit(EXIT_SUCCESS);
}

void sig_winch(int signo){
	struct winsize size;
	ioctl(fileno(stdout), TIOCGWINSZ, (char *) &size);
	resizeterm(size.ws_row, size.ws_col);
}
