fraction: Fraction.o FractionMain.o
	gcc Fraction.o FractionMain.o -lm -g -fsanitize=address -fsanitize=leak -o fraction
	
Fraction.o: Fraction.c Fraction.h
	gcc -Wall -Wextra -lm -g -fsanitize=address -fsanitize=leak -c Fraction.c
	
FractionMain.o: FractionMain.c
	gcc -Wall -Wextra -lm -g -fsanitize=address -fsanitize=leak -c FractionMain.c
	
clean:
	rm -f *.o fraction

rebuild: clean fraction