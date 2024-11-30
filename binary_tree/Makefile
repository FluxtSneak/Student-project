CC = gcc
CFLAGS = -Wall -Wextra -pedantic -g -fsanitize=address -fsanitize=leak
LDFLAGS = -fsanitize=address -fsanitize=leak
SOURCES = $(wildcard *.c)   
OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))

binary_tree: $(OBJECTS) 
	$(CC) $(CFLAGS) -o binary_tree $^ $(LDFLAGS)

binary_tree_lib.o: binary_tree_lib.h

test: test.o

test.o: test.c

.PHONY :clean

clean:
	rm -f *.o 