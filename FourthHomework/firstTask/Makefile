BIN := firstTask
SOURCES := firstTask.c
HEADERS :=
CC := gcc
OBJECTS := firstTask.o
CFLAGS := -g

.PHONY: clean

$(BIN): $(OBJECTS)
	$(CC) -o $(BIN) $(OBJECTS) $(CFLAGS)
$(OBJECTS): $(HEADERS)

clean:
	rm $(BIN) $(OBJECTS)
