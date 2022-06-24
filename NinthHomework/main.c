#include "commander.h"

void sig_winch(int signo);

int main(int argc, char ** argv)
{
	if(argc <= 1){
        printf("Error: no dir name.\n");
        return 0;
    }

    WINDOW * wnd;
	WINDOW * current_wnd;
    WINDOW * left_wnd;
    WINDOW * right_wnd;

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

    left_wnd = derwin(wnd, LINES - 2, commander_area_width, 1, 1);
    right_wnd = derwin(wnd, LINES - 2, commander_area_width, 1, commander_area_width);

    current_wnd = left_wnd;

    box(left_wnd, 0, 0);
    box(right_wnd, 0, 0);

    wrefresh(wnd);

//    DIR * root_dir = opendir(argv[1]);
//    if (!root_dir) {
//        perror("diropen");
//        exit(1);
//    };

    wmove(left_wnd, 1, 1);
    int dir_number = 0;

    struct dirent ** directory_list;
    dir_number = scandir(argv[1], &directory_list, 0, alphasort);

    if (dir_number < 0) perror("scandir");

    for (int i = 0; i < dir_number; ++i) {
        char * dir_type;
        switch (directory_list[i]->d_type) {
            case DT_DIR:
                dir_type = "directory";
                break;
            case DT_CHR:
                dir_type = "text";
                break;
            default:
                dir_type = "unknown";
                break;
        }
        int x, y;
        getyx(left_wnd, y, x);
        wprintw(left_wnd, "%s [%s] %d",
                directory_list[i]->d_name, dir_type, directory_list[i]->d_reclen);

        wmove(left_wnd, y, commander_area_width/3);

        wprintw(left_wnd, "%s [%s] %d",
                directory_list[i]->d_name, dir_type, directory_list[i]->d_reclen);

        wmove(left_wnd, y + 1, 1);
    };

    wrefresh(left_wnd);
    getch();
//    closedir(root_dir);

	delwin(left_wnd);
	delwin(right_wnd);

    while(dir_number--) {
        free(directory_list[dir_number]);
    }
    free(directory_list);

	delwin(wnd);
	endwin();

	exit(EXIT_SUCCESS);
}

void sig_winch(int signo){
	struct winsize size;
	ioctl(fileno(stdout), TIOCGWINSZ, (char *) &size);
	resizeterm(size.ws_row, size.ws_col);
}