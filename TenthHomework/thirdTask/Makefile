BIN := my_commander
SOURCES := main.c
HEADERS := text_editor.h commander.h
CC := gcc
OBJECTS := main.o
EDITOR_LIBRARY := linput
LIBRARY := lteditor
CURSES := lncurses
CFLAGS := -g
OFLAGS := -c

.PHONY: clean

$(BIN): $(OBJECTS) $(LIBFILES)
	$(CC) -o $(BIN) $(OBJECTS) $(CFLAGS) -L. -$(LIBRARY) -$(CURSES)
$(OBJECTS): $(HEADERS)


clean:
	rm -f $(BIN) *.o *.a
