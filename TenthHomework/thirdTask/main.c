#include "my_bash.h"

void sig_winch(int signo);
void clear_resources(WINDOW * main_wnd, int number, struct dirent *** dir_list);
int compare_str(char * first, char * second);
int find_substr(char * string, char * substr);
void merge_string(char ** one, char ** two);
static void backspace(WINDOW * win, size_t * number);
void prepare_wnd(WINDOW * wnd);

int main(int argc, char ** argv)
{
	if(argc <= 1){
        printf("Error: no dir name.\n");
        return 0;
    }

    WINDOW * wnd;
	WINDOW * current_wnd;
    WINDOW * left_wnd;

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

    prepare_wnd(left_wnd);

    wrefresh(wnd);

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
    char * clearWindowCommand = "clear";

    int startFlag = 1;
    while(1) {
        curr_char_number = 0;
        while (((curr_char = wgetch(left_wnd)) != '\n') && (curr_char_number < 100)) {
            if (KEY_BACKSPACE == curr_char) {
                backspace(left_wnd, &curr_char_number);
                continue;
            }
            if(KEY_F(1) == curr_char){
                startFlag = 0;
                break;
            }
            command[curr_char_number++] = curr_char;
            wechochar(left_wnd, curr_char);
        }
        if(0 == startFlag) break;
        command[curr_char_number] = 0;
        int commandFlag = compare_str(command, currentDirCommand);
        if (1 == commandFlag) {
            int y, x;
            getyx(left_wnd, y, x);
            wmove(left_wnd, y + 1, 1);
            wprintw(left_wnd, "%s", curr_path);
            getyx(left_wnd, y, x);
            wmove(left_wnd, y + 1, 1);
            continue;
        }
        commandFlag = compare_str(command, currentDirContent);
        if (1 == commandFlag) {
            int y, x;
            for(size_t i = 0; i < dir_number; ++i){
                getyx(left_wnd, y, x);
                wmove(left_wnd, y + 1, 1);
                wprintw(left_wnd, "%s", directory_list[i]->d_name);
            }
            getyx(left_wnd, y, x);
            wmove(left_wnd, y + 1, 1);
            continue;
        }
        char * finding = strstr(command, currentDirCommand);
        if (NULL != finding) {
            finding += 3;
            if (compare_str(finding, "..")) {
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
            }else{
                if(!compare_str(finding, ".")){
                    if(!compare_str(curr_path, "/")) {
                        merge_string(&curr_path, &splitter);
                    }
                    merge_string(&curr_path, &finding);
                }
            }
            clear_resources(left_wnd,dir_number, &directory_list);
            dir_number = scandir(curr_path, &directory_list, 0, alphasort);
            int y, x;
            getyx(left_wnd, y, x);
            wmove(left_wnd, y + 1, 1);
            wprintw(left_wnd, "%s", curr_path);
            getyx(left_wnd, y, x);
            wmove(left_wnd, y + 1, 1);
            continue;
        }
        commandFlag = compare_str(command, startCommander);
        if (1 == commandFlag) {
            int status;
            pid_t pid = fork();

            if(pid == 0){
                execl("../../NinthHomework/my_commander", "my_commander", curr_path, (char *) NULL);
                exit(0);
            }
            waitpid(pid, &status, 0);
            prepare_wnd(left_wnd);
            continue;
        }
        commandFlag = compare_str(command, clearWindowCommand);
        if (1 == commandFlag) {
            prepare_wnd(left_wnd);
            continue;
        }
        finding = strstr(command, startTextEditor);
        if (NULL != finding) {
            finding += 8;
            int status;
            pid_t pid = fork();

            if(pid == 0){
                execl("../../EighthHomework/text_editor", "text_editor", finding, (char *) NULL);
                exit(0);
            }
            waitpid(pid, &status, 0);
            prepare_wnd(left_wnd);
            continue;
        }
    }

    clear_resources(left_wnd,dir_number, &directory_list);


    delwin(left_wnd);
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

void clear_resources(WINDOW * main_wnd, int number, struct dirent *** dir_list){
    while(number--) {
        free((*dir_list)[number]);
    }
    free((*dir_list));
}

void prepare_wnd(WINDOW * wnd){
    wclear(wnd);
    box(wnd, 0, 0);
    wrefresh(wnd);
    wmove(wnd, 1, 1);
}

int compare_str(char * first, char * second){
    for(size_t i = 0; 1; ++i){
        if(first[i] != second[i]){
            return 0;
        }
        if((first[i] == 0) || (second[i] == 0)) break;
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