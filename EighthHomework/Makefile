BIN := text_editor
SOURCES := main.c
HEADERS := input.h
CC := gcc
OBJECTS := main.o
LIBRARY := linput
CURSES := lncurses
LIBFILES := libinput.a
LIBOBJ := input_command.o input_text.o
CFLAGS := -g
OFLAGS := -c

.PHONY: clean

$(BIN): $(OBJECTS) $(LIBFILES)
	$(CC) -o $(BIN) $(OBJECTS) $(CFLAGS) -L. -$(LIBRARY) -$(CURSES)
$(OBJECTS): $(HEADERS)

$(LIBFILES): $(LIBOBJ)
	ar cr $(LIBFILES) $(LIBOBJ)

input_text.o: input_text.c
	$(CC) $(OFLAGS) input_text.c $(CFLAGS) -L. -$(CURSES)

input_command.o: input_command.c
	$(CC) $(OFLAGS) input_command.c $(CFLAGS) -L. -$(CURSES)

clean:
	rm -f $(BIN) *.o *.a
