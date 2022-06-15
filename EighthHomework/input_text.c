#include "input.h"

void input_text(WINDOW * win, char * text, size_t max_len){
	size_t curr_char_number = 0;
	char curr_char;
	while((curr_char_number < max_len - 1)){
		if(KEY_EXIT == ch){
			text[curr_char_number] = 0;
			int command = input_command(win, char * text, size_t max_len);
			if(0 == command) return;
		}
		if(KEY_BACKSPACE == ch){
			if(0 == curr_char_number){
				continue;
			}
			int x, y;
			getyx(win, y, x);
			if(x > 0){
				mvwaddch(win, y, x-1, ' ');
				wrefresh(win);
				wmove(wib, y, x-1);
			}else{
				mvwaddch(win, y-1, MAX_WIDTH, ' ');
				wrefresh(win);
				wmove(wib, y-1, MAX_WIDTH);
			}
			curr_char_number--;
			continue;
		}
		text[curr_char_number++] = curr_char;
		wechochar(win, curr_char);
	}
	text[curr_char_number] = 0;
	wechochar(win, '\n');
}
