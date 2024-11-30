main:  main.o generic_vector.o
	gcc  main.o generic_vector.o -o generic_vector.x -lm -g -Wall -Wextra -fsanitize=address -fsanitize=leak 

main.o: main.c
	gcc -Wall -Wextra -g -fsanitize=address -fsanitize=leak -c main.c

generic_vector.o: generic_vector.c generic_vector.h
	gcc -Wall -Wextra -g -fsanitize=address -fsanitize=leak -c generic_vector.c

clean:
	rm -f *.o *.x 

rebuild: clean main