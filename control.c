#include <stdio.h>
#include <stdatomic.h>
#include <threads.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

#include "control.h"
#include "snake.h"

Direction_t new_direction = RIGHT;

void set_snake_direction(mtx_t *mtx, cnd_t *cnd, Direction_t direction) {
	if (mtx_lock(mtx) == thrd_error) {
		assert(false && "mtx_lock failed!");
		exit(1);
	}
	new_direction = direction;
	if (mtx_unlock(mtx) == thrd_error) {
		assert(false && "mtx_unlock failed!");
		exit(1);
	}
	if (cnd_signal(cnd) == thrd_error) {
		assert(false && "cnd_signal failed!");
		exit(1);
	}
}

int control(void *context) {
	Control_context_t control_context = *(Control_context_t*)context;
	Snake_t *snake = control_context.snake;
	atomic_bool *game_over = control_context.game_over;
	mtx_t *mtx = control_context.mtx;
	cnd_t *cnd = control_context.cnd;
	if (setvbuf(stdin, NULL, _IONBF, 0) != 0) {
		assert(false && "setvbuf failed!");
		exit(1);
	}
	int c;
	while(true) {
		c = getchar();
		switch (c) {
			case 'W':
			case 'w':
				if (snake->direction == DOWN) break;
				set_snake_direction(mtx, cnd, UP);
				break;
			case 'D':
			case 'd':
				if (snake->direction == LEFT) break;
				set_snake_direction(mtx, cnd, RIGHT);
				break;
			case 'S':
			case 's':
				if (snake->direction == UP) break;
				set_snake_direction(mtx, cnd, DOWN);
				break;
			case 'A':
			case 'a':
				if (snake->direction == RIGHT) break;
				set_snake_direction(mtx, cnd, LEFT);
				break;
			case EOF:
				if (!atomic_load(game_over)) break;
				return 0;
			default:
				break;
		}
	}
	assert(false && "control out of the while(1) loop!");
	return 1;
}
