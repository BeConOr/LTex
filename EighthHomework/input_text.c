#include "input.h"

void input_text(WINDOW ** main_window, WINDOW ** text_window, WINDOW ** command_window, int max_text_window_size, struct TEXT * text, size_t max_len, char * file){
	int curr_char;
    wclear(*command_window);
    wprintw(*command_window, "--INPUT--");
    keypad(*text_window, 1);
    wrefresh(*text_window);
    wrefresh(*command_window);

	while((text->text_length < max_len - 1)){
        curr_char = wgetch (*text_window);
        if(curr_char == KEY_F(1)){
			text->content[text->text_length] = 0;
			int command = input_command(command_window, text->content, file);
			if(0 == command) return;
            wclear(*command_window);
            wprintw(*command_window, "--INPUT--");
            wrefresh(*command_window);
            continue;
		}
		if(KEY_BACKSPACE == curr_char){
			if(0 == text->text_length){
				continue;
			}
			int x, y;
			getyx(*text_window, y, x);
			if(x > 0){
				mvwaddch(*text_window, y, x-1, ' ');
                wrefresh(*text_window);
                wmove(*text_window, y, x-1);
			}else{
                mvwaddch(*text_window, y-1, max_text_window_size, ' ');
                wrefresh(*text_window);
                wmove(*text_window, y-1, max_text_window_size);
			}
			text->text_length--;
			continue;
		}
		text->content[text->text_length++] = curr_char;
		wechochar(*text_window, curr_char);
	}
	text->content[text->text_length] = 0;
}
