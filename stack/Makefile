main:  main.o stacksort.o
	gcc  main.o	stacksort.o -o	stacksort.x -lm -g -Wall -Wextra -fsanitize=address -fsanitize=leak 

main.o: main.c
	gcc -Wall -Wextra -g -fsanitize=address -fsanitize=leak -c main.c

stacksort.o: stacksort.c tris.h
	gcc -Wall -Wextra -g -fsanitize=address -fsanitize=leak -c stacksort.c

clean:
	rm -f *.o *.x 

rebuild: clean main