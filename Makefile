BIN := extractFields
SOURCES := main.c list.c
HEADERS := list.h
CFLAGS := -g
LDFLAGS := -lz

CC := gcc

.PHONY: clean

all: clean $(BIN)

$LD_LIBRARY_PATH=$PWD:$LD_LIBRARY_PATH

$(BIN): $(SOURCES)
		$(CC) $(SOURCES) -o $(BIN) $(CFLAGS) $(LDFLAGS) -O2
$(BIN): $(HEADERS)

clean:	
		rm -rf $(BIN)