EXECBIN = sorting

SOURCES  = sorting.c stats.c shell.c quick.c heap.c batcher.c set.c
OBJECTS = sorting.o stats.o shell.o quick.o heap.o batcher.o set.o

CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic

all: clean $(EXECBIN) format

$(EXECBIN): $(OBJECTS)
	$(CC) -o $(EXECBIN) $(OBJECTS)

sorting.o: sorting.c
	$(CC) $(CFLAGS) -c $(SOURCES)

stats.o: stats.c
	$(CC) $(CFLAGS) -c stats.c

shell.o: shell.c
	$(CC) $(CFLAGS) -c shell.c

heap.o: heap.c
	$(CC) $(CFLAGS) -c heap.c

batcher.o: batcher.c
	$(CC) $(CFLAGS) -c batcher.c

quick.o: quick.c
	$(CC) $(CFLAGS) -c quick.c

set.o: set.c
	$(CC) $(CFLAGS) -c set.c

clean:
	rm -f $(EXECBIN) $(OBJECTS)

format:
	clang-format -i -style=file $(SOURCES) gaps.h set.h stats.h
