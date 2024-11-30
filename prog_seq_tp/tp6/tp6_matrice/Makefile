matrice: matrice.o matriceMain.o
	gcc matrice.o matriceMain.o -lm -g -fsanitize=address -fsanitize=leak -o matrice
	
matrice.o: matrice.c matrice.h
	gcc -Wall -Wextra -lm -g -fsanitize=address -fsanitize=leak -c matrice.c
	
matriceMain.o: matriceMain.c
	gcc -Wall -Wextra -lm -g -fsanitize=address -fsanitize=leak -c matriceMain.c
	
clean:
	rm -f *.o matrice

rebuild: clean matrice