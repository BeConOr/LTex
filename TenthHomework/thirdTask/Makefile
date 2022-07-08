BIN := my_bash
SOURCES := main.c
HEADERS := my_bash.h
CC := gcc
OBJECTS := main.o
LIBRARY :=
CURSES := lncurses
CFLAGS := -g
OFLAGS := -c

.PHONY: clean

$(BIN): $(OBJECTS) $(LIBFILES)
	$(CC) -o $(BIN) $(OBJECTS) $(CFLAGS) -L. $(LIBRARY) -$(CURSES)
$(OBJECTS): $(HEADERS)


clean:
	rm -f $(BIN) *.o *.a
