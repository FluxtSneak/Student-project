main:  main.o queue_tab.o queue_list.o
	gcc  main.o	queue_tab.o queue_list.o -o	queue.x -lm -g -Wall -Wextra -fsanitize=address -fsanitize=leak 

main.o: main.c
	gcc -Wall -Wextra -g -fsanitize=address -fsanitize=leak -c main.c

queue_tab.o: queue_tab.c queue_tab.h
	gcc -Wall -Wextra -g -fsanitize=address -fsanitize=leak -c queue_tab.c


queue_list.o: queue_list.c queue_list.h
	gcc -Wall -Wextra -g -fsanitize=address -fsanitize=leak -c queue_list.c

clean:
	rm -f *.o *.x 

rebuild: clean main