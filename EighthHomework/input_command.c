#include "input.h"

static int compare_str(char * first, char * second);
static void backspace(WINDOW * win, size_t * number);

int input_command(WINDOW ** win, char * text, char * name){
	keypad(*win, TRUE);
    wrefresh(*win);

    char * saveCommand = ":w";
    char * closeCommand = ":q";
    char * closeSaveCommand = ":wq";
    char * continueCommand = "i";

    size_t curr_char_number = 0;
	char curr_char;
	char command[] = {0, 0, 0, 0};
	while(((curr_char = wgetch (*win)) != '\n') && (curr_char_number < 3)){
		if(KEY_F(1) == curr_char){
			return 1;
		}
		if(KEY_BACKSPACE == curr_char){
            backspace(*win, &curr_char_number);
			continue;
		}
		command[curr_char_number++] = curr_char;
		wechochar(*win, curr_char);
	}
    int commandFlag = compare_str(command, saveCommand);
    if(1 == commandFlag) {
        FILE * file = fopen(name, "w");
        fputs(text, file);
        fclose(file);
        return 1;
    }
    commandFlag = compare_str(command, continueCommand);
    if(1 == commandFlag) {
        return 1;
    }
    commandFlag = compare_str(command, closeSaveCommand);
    if(1 == commandFlag) {
        FILE * file = fopen(name, "w");
        fputs(text, file);
        fclose(file);
        return 0;
    }
    commandFlag = compare_str(command, closeCommand);
    if(1 == commandFlag) {
        return 0;
    }
}

static int compare_str(char * first, char * second){
    for(size_t i = 0; (first[i] != 0) && (second[i] != 0); ++i){
        if(first[i] != second[i]){
            return 0;
        }
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
