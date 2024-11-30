tp2: vecteur.o tp2.o MainTP2.o gfx.o
	gcc vecteur.o tp2.o gfx.o MainTP2.o -o tp2.x -lSDL2 -lm -g -Wall -Wextra -fsanitize=address -fsanitize=leak 

vecteur.o: vecteur.c vecteur.h
	gcc -Wall -Wextra -c vecteur.c -g -fsanitize=address -fsanitize=leak

MainTP2.o: MainTP2.c
	gcc -Wall -Wextra -lm -g -fsanitize=address -fsanitize=leak -c MainTP2.c

tp2.o: tp2.c tp2.h
	gcc -Wall -Wextra -c tp2.c -g -lm -fsanitize=address -fsanitize=leak

gfx.o: gfx.c gfx.h
	gcc -Wall -Wextra -c gfx.c

clean:
	rm -f *.o *.x

rebuild: clean tp2