fraction: Fraction.o FractionMain.o
	gcc Fraction.o FractionMain.o -lm -o fraction
	
Fraction.o: Fraction.c Fraction.h
	gcc -Wall -Wextra -lm -c Fraction.c
	
FractionMain.o: FractionMain.c
	gcc -Wall -Wextra -lm -c FractionMain.c
	
clean:
	rm -f *.o fraction

rebuild: clean fraction