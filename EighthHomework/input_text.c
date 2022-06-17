#include "input.h"

void input_text(WINDOW ** text_window, WINDOW ** command_window, int max_text_window_size, char * text, size_t max_len, char * file){
    size_t curr_char_number = 0;
	char curr_char;
	while((curr_char_number < max_len - 1)){
        curr_char = wgetch (*text_window);
        if(KEY_BREAK == curr_char){
			text[curr_char_number] = 0;
			int command = input_command(*command_window, text, max_len, file);
			if(0 == command) return;
		}
        if('\n' == curr_char){
            wechochar(*text_window, '\n');
            refresh();
        }
		if(KEY_BACKSPACE == curr_char){
			if(0 == curr_char_number){
				continue;
			}
			int x, y;
			getyx(*text_window, y, x);
			if(x > 0){
				wmove(*text_window, y, x-2);
                wprintw(*text_window, "  ");
                wrefresh(*text_window);
                wmove(*text_window, y, x-2);
			}else{
				wmove(*text_window, y-1, max_text_window_size-1);
                wprintw(*text_window, "  ");
                wrefresh(*text_window);
                wmove(*text_window, y-1, max_text_window_size-1);
			}
			curr_char_number--;
			continue;
		}
		text[curr_char_number++] = curr_char;
		wechochar(wins.text_window, curr_char);
	}
	text[curr_char_number] = 0;
}
