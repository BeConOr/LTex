#include "input.h"

void input_text(struct INPUT_WINDOWS wins, char * text, size_t max_len){
	size_t curr_char_number = 0;
	char curr_char;
	while((curr_char_number < max_len - 1)){
		if(KEY_EXIT == ch){
			text[curr_char_number] = 0;
			int command = input_command(wins.command_window, char * text, size_t max_len);
			if(0 == command) return;
		}
		if(KEY_BACKSPACE == ch){
			if(0 == curr_char_number){
				continue;
			}
			int x, y;
			getyx(wins.text_window, y, x);
			if(x > 0){
				mvwaddch(wins.text_window, y, x-1, ' ');
				wrefresh(wins.text_window);
				wmove(wins.text_window, y, x-1);
			}else{
				mvwaddch(wins.text_window, y-1, wins.max_text_window_size, ' ');
				wrefresh(wins.text_window);
				wmove(wins.text_window, y-1, wins.max_text_window_size);
			}
			curr_char_number--;
			continue;
		}
		text[curr_char_number++] = curr_char;
		wechochar(wins.text_window, curr_char);
	}
	text[curr_char_number] = 0;
}
