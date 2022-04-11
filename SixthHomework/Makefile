BIN := phone_book
SOURCES := phone_book.c
HEADERS :=
CC := gcc
OBJECTS := phone_book.o
CFLAGS := -g

.PHONY: clean

$(BIN): $(OBJECTS)
	$(CC) -o $(BIN) $(OBJECTS) $(CFLAGS)
$(OBJECTS): $(HEADERS)

clean:
	rm $(BIN) $(OBJECTS)
