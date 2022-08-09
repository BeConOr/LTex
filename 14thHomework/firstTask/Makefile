BIN_REC := reciever
BIN_SEND := sender
SOURCES_REC := reciever.c
SOURCES_SEND := sender.c
HEADERS_REC := 
HEADERS_SEND := 
CC := gcc
OBJECTS_REC := reciever.o
OBJECTS_SEND := sender.o
POSIX_QUEUE := lrt
CFLAGS := -g
OFLAGS := -c

.PHONY: clean

$(BIN_REC): $(OBJECTS_REC) $(LIBFILES)
	$(CC) -o $(BIN_REC) $(OBJECTS_REC) $(CFLAGS) -L. -$(POSIX_QUEUE)
$(OBJECTS_REC): $(HEADERS_REC)

$(BIN_SEND): $(OBJECTS_SEND) $(LIBFILES)
	$(CC) -o $(BIN_SEND) $(OBJECTS_SEND) $(CFLAGS) -L. -$(POSIX_QUEUE)
$(OBJECTS_SEND): $(HEADERS_SEND)


clean:
	rm -f $(BIN_REC) $(BIN_SEND) *.o *.a
