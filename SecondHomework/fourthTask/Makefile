BIN := fourthTask
SOURCES := fourthTask.c
HEADERS :=
CC := gcc
OBJECTS := fourthTask.o
CFLAGS := -g

.PHONY: clean

$(BIN): $(OBJECTS)
	$(CC) -o $(BIN) $(OBJECTS) $(CFLAGS)
$(OBJECTS): $(HEADERS)

clean:
	rm $(BIN) $(OBJECTS)
