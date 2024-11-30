tableaux: tableaux.o main.o gfx.o
	gcc tableaux.o main.o gfx.o -lSDL2 -o tableaux 

tableaux.o: tableaux.c tableaux.h
	gcc -Wall -Wextra -c tableaux.c

main.o: main.c
	gcc -Wall -Wextra -c main.c
gfx.o: gfx.c gfx.h
	gcc -Wall -Wextra -c gfx.c
clean:
	rm -f *.o tableaux

rebuild: clean tableaux