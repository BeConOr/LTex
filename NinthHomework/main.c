#include "commander.h"

void sig_winch(int signo);
int open_target_dir(WINDOW * main_wnd, char * name, struct dirent *** dir_list, WINDOW *** wnd_list, int width);
void clear_resources(WINDOW * main_wnd, int number, struct dirent *** dir_list, WINDOW *** wnd_list);
int compare_str(char * first, char * second);
void merge_string(char ** one, char ** two);

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
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_BLACK, COLOR_WHITE);
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
    WINDOW ** points_list_wnd;
    char * curr_path = malloc(1024);
    strcpy(curr_path, argv[1]);
    char * dr_name = malloc(1224);
    char * temp_name = malloc(200);
    char * splitter = "/";

    dir_number = open_target_dir(left_wnd, argv[1], &directory_list, &points_list_wnd, commander_area_width);

    keypad(left_wnd, 1);
    size_t current_point = 0;
    int curr_char;
    while ((curr_char = wgetch(left_wnd))) {
        if((KEY_UP == curr_char) || (KEY_DOWN == curr_char)) {
            wattron(points_list_wnd[current_point], COLOR_PAIR(1));
            wbkgd(points_list_wnd[current_point], COLOR_PAIR(1));
            wrefresh(points_list_wnd[current_point]);
            if (KEY_UP == curr_char) {
                if (current_point > 0) {
                    current_point--;
                }
            }
            if (KEY_DOWN == curr_char) {
                if (current_point < dir_number - 1) {
                    current_point++;
                }
            }
            wattron(points_list_wnd[current_point], COLOR_PAIR(2));
            wbkgd(points_list_wnd[current_point], COLOR_PAIR(2));
            wrefresh(points_list_wnd[current_point]);
        }
        if('\n' == curr_char){
            if(DT_DIR == directory_list[current_point]->d_type) {
                strcpy(dr_name, directory_list[current_point]->d_name);
                if (compare_str(directory_list[current_point]->d_name, "..")) {
                    if(!compare_str(curr_path, "/")) {
                        size_t sl_pos = 0;
                        for (size_t i = 0; curr_path[i] != 0; ++i) {
                            if('/' == curr_path[i]) sl_pos = i;
                        }
                        if(sl_pos != 0) {
                            curr_path[sl_pos] = 0;
                        }else{
                            curr_path[1] = 0;
                        }
                    }
                }
                else{
                    if(!compare_str(directory_list[current_point]->d_name, ".")){
                        //strcpy(temp_name, directory_list[current_point]->d_name);
                        //snprintf(dr_name, 1224, "%s%c%s", curr_path, '/', temp_name);
                        merge_string(&curr_path, &splitter);
                        merge_string(&curr_path, &dr_name);
                    }
                }
                strcpy(dr_name, curr_path);
                clear_resources(left_wnd, dir_number, &directory_list, &points_list_wnd);
                wclear(left_wnd);
                dir_number = open_target_dir(left_wnd, dr_name, &directory_list, &points_list_wnd,
                                             commander_area_width);
                current_point = 0;
                wrefresh(left_wnd);
            }
//            if(DT_CHR == directory_list[current_point]->d_type){
//                strcpy(temp_name, directory_list[current_point]->d_name);
//                snprintf(dr_name, 1224, "%s%c%s", curr_path, '/', temp_name);
//                edit_text_file(dr_name);
//            }
        }
        if(KEY_F(1) == curr_char){
            break;
        }
    }

    clear_resources(left_wnd,dir_number, &directory_list, &points_list_wnd);

//    while(dir_number--) {
//        free(directory_list[dir_number]);
//        delwin(points_list_wnd[dir_number]);
//    }
//    free(directory_list);
//    free(points_list_wnd);

    delwin(left_wnd);
    delwin(right_wnd);
    delwin(wnd);
	endwin();

	exit(EXIT_SUCCESS);
}

void sig_winch(int signo){
	struct winsize size;
	ioctl(fileno(stdout), TIOCGWINSZ, (char *) &size);
	resizeterm(size.ws_row, size.ws_col);
}

void merge_string(char ** one, char ** two){
    size_t nul_pos = 0;

    while((*one)[nul_pos] != 0){
        nul_pos++;
    }
    for(size_t i = 0; (*two)[i] != 0; ++i){
        (*one)[nul_pos++] = (*two)[i];
    }
    (*one)[nul_pos] = 0;
}

void clear_resources(WINDOW * main_wnd, int number, struct dirent *** dir_list, WINDOW *** wnd_list){
    while(number--) {
        free((*dir_list)[number]);
        delwin((*wnd_list)[number]);
    }
    free((*dir_list));
    free((*wnd_list));
}

int compare_str(char * first, char * second){
    for(size_t i = 0; 1; ++i){
        if(first[i] != second[i]){
            return 0;
        }
        if((first[i] == 0) && (second[i] == 0)) break;
    }
    return 1;
}

int open_target_dir(WINDOW * main_wnd, char * name, struct dirent *** dir_list, WINDOW *** wnd_list, int width){
    int dir_number = scandir(name, dir_list, 0, alphasort);
    *wnd_list = malloc(sizeof(WINDOW *) * dir_number);

    if (dir_number < 0) perror("scandir");

    for (int i = 0; i < dir_number; ++i) {
        char * dir_type;
        switch ((*dir_list)[i]->d_type) {
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
        getyx(main_wnd, y, x);
        (*wnd_list)[i] = derwin(main_wnd, 1, width - 2, y, x);
        if(i == 0){
            wattron((*wnd_list)[i], COLOR_PAIR(2));
            wbkgd((*wnd_list)[i], COLOR_PAIR(2));
        }
        wprintw((*wnd_list)[i], "%s [%s] %d",
                (*dir_list)[i]->d_name, dir_type, (*dir_list)[i]->d_reclen);

        wmove(main_wnd, y + 1, 1);
    };

    wrefresh(main_wnd);
    return dir_number;
}