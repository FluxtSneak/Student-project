


CC=gcc -Wall -Wextra -g -fsanitize=leak -fsanitize=undefined -fsanitize=address
LIBS=-lSDL2

arr1D.x: main.o arr1D.o gfx.o
	$(CC) $^ -o $@ $(LIBS)

main.o: main.c
	$(CC) -c $< $(LIBS)

arr1D.o: arr1D.c arr1D.h
	$(CC) -c $< $(LIBS)

gfx.o: gfx.c gfx.h
	$(CC) -c $< $(LIBS)

clean:
	@rm -f *.o arr1D.x




# arr1D: arr1D.o main.o gfx.o 
# 	gcc arr1D.o main.o gfx.o -o arr1D.x -lm -LSDL2


# arr1D.o: arr1D.c arr1D.h 
# 	gcc -Wall -Wextra -c arr1D.c

# gfx.o: gfx.h gfx.c
# 	gcc -Wall -Wextra -c gfx.c 


# main.o: main.c
# 	gcc -Wall -Wextra -c main.c

# clean:
# 	rm -f *.o arr1D

# rebuild: clean arr1D


# arr1D: arr1D.o main.o
# 	gcc arr1D.o main.o -o arr1D -Wall -Wextra -std=c11 -g -fsanitize=leak -fsanitize=undefined  -fsanitize=address -LSDL2

# arr1D.o: arr1D.c arr1D.h
# 	gcc -Wall -Wextra -c arr1D.c -Wall -Wextra -std=c11 -g -fsanitize=leak -fsanitize=undefined  -fsanitize=address -LSDL2

# main.o: main.c 
# 	gcc -Wall -Wextra -c main.c -Wall -Wextra -std=c11 -g -fsanitize=leak -fsanitize=undefined  -fsanitize=address -LSDL2


# clean: 
# 	@rm -f *.o arr1D 

# rebuild: clean arr1D