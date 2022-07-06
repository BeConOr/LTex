#include "my_bash.h"

void sig_winch(int signo);
void clear_resources(WINDOW * main_wnd, int number, struct dirent *** dir_list, WINDOW *** wnd_list);
int compare_str(char * first, char * second);
void merge_string(char ** one, char ** two);
static void backspace(WINDOW * win, size_t * number);

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

    int commander_area_width = COLS - 2;

    left_wnd = derwin(wnd, LINES - 2, commander_area_width, 1, 1);

    current_wnd = left_wnd;

    box(left_wnd, 0, 0);

    wrefresh(wnd);

    wmove(left_wnd, 1, 1);
    int dir_number = 0;

    struct dirent ** directory_list;
    //WINDOW ** points_list_wnd;
    char * curr_path = malloc(1024);
    strcpy(curr_path, argv[1]);
    char * dr_name = malloc(1224);
    char * temp_name = malloc(200);
    char * splitter = "/";

    dir_number = scandir(argv[1], &directory_list, 0, alphasort);

    keypad(left_wnd, 1);
    size_t current_point = 0;
    size_t curr_char_number = 0;
    int curr_char;
    char command[100] = {0};
    char * currentDirCommand = "cd";
    char * currentDirContent = "ls";
    char * startCommander = "mcmnd";
    char * startTextEditor = "teditor";

    while(1) {
        while (((curr_char = wgetch(*win)) != '\n') && (curr_char_number < 100)) {
            if (KEY_BACKSPACE == curr_char) {
                backspace(left_wnd, &curr_char_number);
                continue;
            }
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
            command[curr_char_number++] = curr_char;
            wechochar(*win, curr_char);
        }
        command[curr_char_number] = 0;
        int commandFlag = compare_str(command, cd);
        if (1 == commandFlag) {
            int y, x;
            getyx(left_wnd, y, x);
            wmove(left_wnd, y + 1, 0);
            wprintw(left_wnd, "%s", curr_path);
            FILE *file = fopen(name, "w");
            fputs(text, file);
            fclose(file);
            return 1;
        }
        commandFlag = compare_str(command, continueCommand);
        if (1 == commandFlag) {
            return 1;
        }
        commandFlag = compare_str(command, closeSaveCommand);
        if (1 == commandFlag) {
            FILE *file = fopen(name, "w");
            fputs(text, file);
            fclose(file);
            return 0;
        }
        commandFlag = compare_str(command, closeCommand);
        if (1 == commandFlag) {
            return 0;
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


static void backspace(WINDOW * win, size_t * number){
    if(0 == *number){
        return;
    }
    int x, y;
    getyx(win, y, x);
    mvwaddch(win, y, x-1, ' ');
    wrefresh(win);
    wmove(win, y, x-1);
    (*number)--;
}