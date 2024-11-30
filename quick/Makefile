main:  main.o quicksort.o
	gcc  main.o	quicksort.o -o	quicksort.x -lm -g -Wall -Wextra -fsanitize=address -fsanitize=leak 

main.o: main.c
	gcc -Wall -Wextra -g -fsanitize=address -fsanitize=leak -c main.c

quicksort.o: quicksort.c tris.h
	gcc -Wall -Wextra -g -fsanitize=address -fsanitize=leak -c quicksort.c

clean:
	rm -f *.o *.x 

rebuild: clean main