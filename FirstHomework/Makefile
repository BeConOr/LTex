BIN := bitOperation
SOURCES := bitOperation.c
HEADERS :=
CC := gcc
OBJECTS := bitOperation.o
CFLAGS := -g

.PHONY: clean

$(BIN): $(OBJECTS)
	$(CC) -o $(BIN) $(OBJECTS) $(CFLAGS)
$(OBJECTS): $(HEADERS)

clean:
	rm $(BIN) $(OBJECTS)
