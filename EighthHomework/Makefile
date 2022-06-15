BIN := text_editor
SOURCES := main.c
HEADERS := input.h
CC := gcc
OBJECTS := main.o
LIBRARY := lncurses linput
LIBFILES := libinput.a
LIBOBJ := input_text.o input_command.o
CFLAGS := -g
OFLAGS := -c

.PHONY: clean

$(BIN): $(OBJECTS) $(LIBFILES)
	$(CC) -o $(BIN) $(OBJECTS) $(CFLAGS) -L. -$(LIBRARY)
$(OBJECTS): $(HEADERS)

$(LIBFILES): $(LIBOBJ)
	ar cr $(LIBFILES) $(LIBOBJ)

input_text.o: input_text.c
	$(CC) $(OFLAGS) input_text.c

input_command.o: input_command.c
	$(CC) $(OFLAGS) input_command.c

clean:
	rm -f $(BIN) *.o *.a
