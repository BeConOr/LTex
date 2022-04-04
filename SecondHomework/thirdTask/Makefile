BIN := thirdTask
SOURCES := thirdTask.c
HEADERS :=
CC := gcc
OBJECTS := thirdTask.o
CFLAGS := -g

.PHONY: clean

$(BIN): $(OBJECTS)
	$(CC) -o $(BIN) $(OBJECTS) $(CFLAGS)
$(OBJECTS): $(HEADERS)

clean:
	rm $(BIN) $(OBJECTS)
