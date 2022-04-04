BIN := secondTask
SOURCES := secondTask.c
HEADERS :=
CC := gcc
OBJECTS := secondTask.o
CFLAGS := -g

.PHONY: clean

$(BIN): $(OBJECTS)
	$(CC) -o $(BIN) $(OBJECTS) $(CFLAGS)
$(OBJECTS): $(HEADERS)

clean:
	rm $(BIN) $(OBJECTS)
