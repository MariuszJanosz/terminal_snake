#include <stdio.h>

#include "control.h"
#include "snake.h"

Direction_t new_direction = RIGHT;

int control(void *context) {
	Snake_t *snake = (Snake_t*)context;
	setvbuf(stdin, NULL, _IONBF, 0);
	int c;
	while(true) {
		c = getchar();
		switch (c) {
			case 'W':
			case 'w':
				if (snake->direction == DOWN) break;
				new_direction = UP;
				break;
			case 'D':
			case 'd':
				if (snake->direction == LEFT) break;
				new_direction = RIGHT;
				break;
			case 'S':
			case 's':
				if (snake->direction == UP) break;
				new_direction = DOWN;
				break;
			case 'A':
			case 'a':
				if (snake->direction == RIGHT) break;
				new_direction = LEFT;
				break;
			default:
				break;
		}
	}
	return 1;
}
