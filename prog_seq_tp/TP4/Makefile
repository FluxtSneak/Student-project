tableaux: tableaux.o main.o
	gcc tableaux.o main.o -o tableaux
	
tableaux.o: tableaux.c tableaux.h
	gcc -Wall -Wextra -c tableaux.c
	
main.o: main.c
	gcc -Wall -Wextra -c main.c
	
clean:
	rm -f *.o tableaux

rebuild: clean tableaux