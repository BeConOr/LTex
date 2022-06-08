BIN := text_editor
SOURCES := main.c
HEADERS := 
CC := gcc
OBJECTS := main.o
LIBRARY := lncurses
CFLAGS := -g
OFLAGS := -c

.PHONY: clean

$(BIN): $(OBJECTS) $(LIBFILES)
	$(CC) -o $(BIN) $(OBJECTS) $(CFLAGS) -L. -$(LIBRARY)
$(OBJECTS): $(HEADERS)

clean:
	rm -f $(BIN) *.o *.a
