main: main.o
	gcc -fsanitize=address -fsanitize=leak main.o

main.o: main.c 
	gcc -c main.c -Wall -Wextra -fsanitize=address -fsanitize=leak

test: test.o
	gcc -fsanitize=address -fsanitize=leak test.o

test.o: test.o
	gcc -c test.c -Wall -Wextra -fsanitize=address -fsanitize=leak

clean:
	rm -f *.o main

rebuild: clean main