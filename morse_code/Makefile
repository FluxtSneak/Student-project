CC = gcc
CFLAGS = -Wall -Wextra -pedantic -g -fsanitize=address -fsanitize=leak
LDFLAGS = -fsanitize=address -fsanitize=leak
SOURCES = $(wildcard *.c)   
OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))

morse: $(OBJECTS) 
	$(CC) $(CFLAGS) -o morse $^ $(LDFLAGS)

morse.o: morse.h

test: test.o

test.o: test.c

.PHONY :clean

clean:
	rm -f *.o 