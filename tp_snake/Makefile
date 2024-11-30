main:  main.o snake.o gfx.o queue_list.o
	gcc  main.o	gfx.o snake.o queue_list.o -o snake.x -lm -g -Wall -Wextra -fsanitize=address -fsanitize=leak -lSDL2

main.o: main.c
	gcc -Wall -Wextra -g -fsanitize=address -fsanitize=leak -c main.c

snake.o: snake.c snake.h
	gcc -Wall -Wextra -g -fsanitize=address -fsanitize=leak -c snake.c

queue_list.o: queue_list.c queue_list.h
	gcc -Wall -Wextra -g -fsanitize=address -fsanitize=leak -c queue_list.c

gfx.o: gfx.c gfx.h
	gcc -Wall -Wextra -g -fsanitize=address -fsanitize=leak -c gfx.c

clean:
	rm -f *.o *.x 

rebuild: clean main