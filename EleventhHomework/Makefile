BIN := multi_thread
SOURCES := main.c
HEADERS := 
CC := gcc
OBJECTS := main.o
PTHREAD := lpthread
CFLAGS := -g
OFLAGS := -c

.PHONY: clean

$(BIN): $(OBJECTS) $(LIBFILES)
	$(CC) -o $(BIN) $(OBJECTS) $(CFLAGS) -L. -$(PTHREAD)
$(OBJECTS): $(HEADERS)


clean:
	rm -f $(BIN) *.o *.a
