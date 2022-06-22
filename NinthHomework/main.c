#include <termios.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <stdlib.h>
#include <ncurses.h>
#include <malloc.h>
#include "input.h"
#include <stdio.h>

#define MAX_DOC_SIZE 20971520

void sig_winch(int signo);

int main(int argc, char ** argv)
{
	if(argc <= 1){
        printf("Error: no file name.\n");
        return 0;
    }

    WINDOW * wnd;
	WINDOW * text_wnd;
    WINDOW * command_wnd;

    struct TEXT text;
	
	text.content = (char *) malloc(MAX_DOC_SIZE * sizeof(char));
    text.text_length = 0;
	
	initscr();
	signal(SIGWINCH, sig_winch);
	cbreak();
    noecho();
	curs_set(0);
	start_color();
	refresh();

	wnd = newwin(LINES, COLS, 0, 0);
//    keypad(wnd, 1);
	box(wnd, 0, 0);

    int input_area_width = COLS - 2;
    int command_area_height = 1;
    int text_area_height = LINES - command_area_height - 1;

    text_wnd = derwin(wnd, text_area_height, input_area_width, 1, 1);
    command_wnd = derwin(wnd, command_area_height, input_area_width, text_area_height, 1);

    FILE * file = fopen(argv[1], "r");
    if(file != NULL){
        char curr_char;
        while((curr_char = fgetc(file)) != EOF){
            waddch(text_wnd, curr_char);
            text.content[text.text_length++] = curr_char;
        }
        fclose(file);
    }

    wrefresh(wnd);

    input_text(&wnd, &text_wnd, &command_wnd, input_area_width, &text, MAX_DOC_SIZE, argv[1]);

    free(text.content);

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