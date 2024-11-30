CC = gcc
CFLAGS = -Wall -Wextra -pedantic -g -fsanitize=address -fsanitize=leak
LDFLAGS = -fsanitize=address -fsanitize=leak -lm
SOURCES = $(wildcard *.c)   
OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))

pointer_sort: $(OBJECTS) 
	$(CC) $(CFLAGS) -o pointer_sort $^ $(LDFLAGS)

pointer_sort.o: pointer_sort.h

test: test.o

test.o: test.c

.PHONY :clean

clean:
	rm -f *.o 