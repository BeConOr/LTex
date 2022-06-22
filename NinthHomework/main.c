#include "commander.h"

void sig_winch(int signo);

int main(int argc, char ** argv)
{
	if(argc <= 1){
        printf("Error: no dir name.\n");
        return 0;
    }

    WINDOW * wnd;
	struct windows_list * wnd_list = (struct windows_list*) malloc(sizeof(struct windows_list));
    wnd_list->next = (struct windows_list*) malloc(sizeof(struct windows_list));
    wnd_list->previous = wnd_list->next;
    wnd_list->next->next = wnd_list;
    wnd_list->next->previous = wnd_list->next->next;

	initscr();
	signal(SIGWINCH, sig_winch);
	cbreak();
    noecho();
	curs_set(0);
	start_color();
	refresh();

	wnd = newwin(LINES, COLS, 0, 0);
	box(wnd, 0, 0);

    int commander_area_width = (COLS - 2)/2;

    wnd_list->value = derwin(wnd, LINES - 2, commander_area_width, 1, 1);
    wnd_list->next->value = derwin(wnd, LINES - 2, commander_area_width, 1, commander_area_width);

    wrefresh(wnd);

	delwin(wnd_list->value);
	delwin(wnd_list->next->value);

    free(wnd_list->next);
    free(wnd_list);

	delwin(wnd);
	endwin();

	exit(EXIT_SUCCESS);
}

void sig_winch(int signo){
	struct winsize size;
	ioctl(fileno(stdout), TIOCGWINSZ, (char *) &size);
	resizeterm(size.ws_row, size.ws_col);
}