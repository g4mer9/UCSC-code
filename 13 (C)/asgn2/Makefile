EXECBIN = mathlib-test

SOURCES  = $(wildcard *.c)
OBJECTS = mathlib-test.o e.o euler.o viete.o bbp.o madhava.o newton.o
LDFLAGS = -lm

CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic

all: clean $(EXECBIN) format

$(EXECBIN): $(OBJECTS)
	$(CC) $(LDFLAGS) -o $(EXECBIN) $(OBJECTS)

mathlib-test.o: mathlib-test.c
	$(CC) $(CFLAGS) -c mathlib-test.c e.c euler.c bbp.c viete.c madhava.c newton.c

e.o: e.c
	$(CC) $(CFLAGS) -c e.c

euler.o: euler.c
	$(CC) $(CFLAGS) -c euler.c

bbp.o: bbp.c
	$(CC) $(CFLAGS) -c bbp.c

viete.o: viete.c
	$(CC) $(CFLAGS) -c viete.c

madhava.o: madhava.c
	$(CC) $(CFLAGS) -c madhava.c

newton.o: newton.c
	$(CC) $(CFLAGS) -c newton.c

clean:
	rm -f $(EXECBIN) $(OBJECTS)

format:
	clang-format -i -style=file newton.c
	clang-format -i -style=file e.c
	clang-format -i -style=file euler.c
	clang-format -i -style=file madhava.c
	clang-format -i -style=file viete.c
	clang-format -i -style=file bbp.c
	clang-format -i -style=file mathlib-test.c
