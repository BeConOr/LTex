#include <termios.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <stdlib.h>
#include <curses.h>
#include <malloc.h>

#define MAX_DOC_SIZE 20971520

void sig_winch(int signo);

void text_input(WINDOW * win, size_t max_len);

int main(void)
{
	WINDOW * wnd;
	WINDOW * subwnd;
	
	char * text = (char *) alloc(MAX_DOC_SIZE * sizeof(char));
	
	initscr();
	signal(SIGWINCH, sig_winch);
	cbreak();
	curs_set(0);
	start_color();
	refresh();
	wnd = newwin(6, 18, 2, 4);
	box(wnd, '|', '-');
	subwnd = derwin(wnd, 4, 16, 1, 1);
	wprintw(subwnd, "Hello, brave new curses world!\n");
	wrefresh(wnd);
	delwin(subwnd);
	delwin(wnd);
	move(9, 0);
	printw("Press any key to continue...");
	refresh();
	getch();
	endwin();
	exit(EXIT_SUCCESS);
}

void sig_winch(int signo){
	struct winsize size;
	ioctl(fileno(stdout), TIOCGWINSZ, (char *) &size);
	resizeterm(size.ws_row, size.ws_col);
}

void text_input(WINDOW * win, size_t max_len){
	
}