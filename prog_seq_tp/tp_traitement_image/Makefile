pgmMain: matrice.o pgmMain.o pgm.o gfx.o
	gcc matrice.o pgmMain.o gfx.o pgm.o -o pgm.x -lm -lSDL2 -g -Wall -Wextra -fsanitize=address -fsanitize=leak 

pgm.o: pgm.c pgm.h
	gcc -Wall -Wextra -c pgm.c -g -fsanitize=address -fsanitize=leak

matrice.o: matrice.c matrice.h
	gcc -Wall -Wextra -g -fsanitize=address -fsanitize=leak -c matrice.c

pgmMain.o: pgmMain.c
	gcc -Wall -Wextra -g -fsanitize=address -fsanitize=leak -c pgmMain.c

gfx.o: gfx.c gfx.h
	gcc -Wall -Wextra -c gfx.c

clean:
	rm -f *.o *.x 

rebuild: clean pgmMain