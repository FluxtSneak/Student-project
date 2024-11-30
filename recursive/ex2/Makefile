main: main.o rec.o
	gcc -fsanitize=address -fsanitize=leak main.o rec.o

main.o: main.c 
	gcc -c main.c -Wall -Wextra -fsanitize=address -fsanitize=leak

test: test.o rec.o
	gcc rec.o test.o -fsanitize=address -fsanitize=leak -o test.x

test.o: test.c rec.o
	gcc -c test.c rec.c -Wall -Wextra -fsanitize=address -fsanitize=leak

rec.o : rec.c rec.h
	gcc -Wall -Wextra -g -fsanitize=address -fsanitize=leak -c rec.c

clean:
	rm -f *.o main

rebuild: clean main