BIN := second
SOURCES := main.c
HEADERS :=
CC := gcc
OBJECTS := main.o
CFLAGS := -g

.PHONY: clean

$(BIN): $(OBJECTS)
	$(CC) -o $(BIN) $(OBJECTS) $(CFLAGS)
$(OBJECTS): $(HEADERS)

clean:
	rm -f $(BIN) *.o
