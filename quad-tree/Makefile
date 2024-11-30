CC = gcc
CFLAGS = -Wall -Wextra -pedantic -g -fsanitize=address -fsanitize=leak
LDFLAGS = -fsanitize=address -fsanitize=leak -lm
SOURCES = $(wildcard *.c)   
OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))

quad_tree: $(OBJECTS) 
	$(CC) $(CFLAGS) -o quad_tree $^ $(LDFLAGS)

quad_tree.o: quad_tree.h

test: test.o

test.o: test.c

.PHONY :clean

clean:
	rm -f *.o 