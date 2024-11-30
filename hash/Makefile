CC = gcc
CFLAGS = -Wall -Wextra -pedantic -g -fsanitize=address -fsanitize=leak
LDFLAGS = -fsanitize=address -fsanitize=leak
SOURCES = $(wildcard *.c)   
OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))

hash: $(OBJECTS) 
	$(CC) $(CFLAGS) -o hash $^ $(LDFLAGS)

hash.o: hash.h

test: test.o

test.o: test.c

.PHONY :clean

clean:
	rm -f *.o 