#include "input.h"

void input_text(WINDOW * win, char * text, size_t max_len){
	size_t curr_char_number = 0;
	char curr_char;
	char * command = {0, 0, 0, 0};
	while((curr_char = wgetch (win)) && (curr_char_number < 3)){
		if(KEY_EXIT == ch){
			return 1;
		}
		if(KEY_BACKSPACE == ch){
			if(0 == curr_char_number){
				continue;
			}
			int x, y;
			getyx(win, y, x);
			mvwaddch(win, y, x-1, ' ');
			wrefresh(win);
			wmove(wib, y, x-1);
			curr_char_number--;
			continue;
		}
		command[curr_char_number++] = curr_char;
		wechochar(win, curr_char);
	}
	wechochar(win, '\n');
}
