CC = gcc
CFLAGS = -Wall -Wextra -pedantic -g -fsanitize=address -fsanitize=leak
LDFLAGS = -fsanitize=address -fsanitize=leak
SOURCES = $(wildcard *.c)   
OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))  

calculator: $(OBJECTS) 
	$(CC) $(CFLAGS) -o calculator $^ $(LDFLAGS)

pile.o: pile.h


#regle implicites:
#galaxy.o: galaxy.c
#	$(CC) -c galaxy.c $(CFLAGS)

#stars.o: stars.c
#	$(CC) -c stars.c $(CFLAGS)

#vec.o: vec.c
#	$(CC) -c vec.c $(CFLAGS)

.PHONY :clean

clean:
	rm -f *.o 