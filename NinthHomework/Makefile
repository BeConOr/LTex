BIN := my_commander
SOURCES := main.c
EDITOR_HEADERS := input.h
HEADERS := text_editor.h commander.h
CC := gcc
OBJECTS := main.o
EDITOR_LIBRARY := linput
LIBRARY := lteditor
CURSES := lncurses
LIBFILES := libteditor.a
EDITOR_LIBFILES := libinput.a
EDITOR_LIBOBJ := input_command.o input_text.o
LIBOBJ := text_editor.o
CFLAGS := -g
OFLAGS := -c

.PHONY: clean

$(BIN): $(OBJECTS) $(LIBFILES)
	$(CC) -o $(BIN) $(OBJECTS) $(CFLAGS) -L. -$(LIBRARY) -$(CURSES)
$(OBJECTS): $(HEADERS)

$(LIBFILES): $(LIBOBJ)
	ar cr $(LIBFILES) $(LIBOBJ)

$(EDITOR_LIBFILES): $(EDITOR_LIBOBJ)
	ar cr $(EDITOR_LIBFILES) $(EDITOR_LIBOBJ)

input_text.o: input_text.c
	$(CC) $(OFLAGS) input_text.c $(CFLAGS) -L. -$(CURSES)

input_command.o: input_command.c
	$(CC) $(OFLAGS) input_command.c $(CFLAGS) -L. -$(CURSES)

text_editor.o: text_editor.c
	$(CC) $(OFLAGS) text_editor.c $(CFLAGS) -L. -$(EDITOR_LIBRARY) -$(CURSES)

clean:
	rm -f $(BIN) *.o *.a
