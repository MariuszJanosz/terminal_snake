#include <stdio.h>
#include <stdatomic.h>
#include <threads.h>
#include <assert.h>
#include <stdbool.h>

#include "control.h"
#include "snake.h"

Direction_t new_direction = RIGHT;

int control(void *context) {
	Control_context_t control_context = *(Control_context_t*)context;
	Snake_t *snake = control_context.snake;
	atomic_bool *game_over = control_context.game_over;
	mtx_t *mtx = control_context.mtx;
	cnd_t *cnd = control_context.cnd;
	setvbuf(stdin, NULL, _IONBF, 0);
	int c;
	while(true) {
		c = getchar();
		switch (c) {
			case 'W':
			case 'w':
				if (snake->direction == DOWN) break;
				mtx_lock(mtx);
				new_direction = UP;
				mtx_unlock(mtx);
				cnd_signal(cnd);
				break;
			case 'D':
			case 'd':
				if (snake->direction == LEFT) break;
				mtx_lock(mtx);
				new_direction = RIGHT;
				mtx_unlock(mtx);
				cnd_signal(cnd);
				break;
			case 'S':
			case 's':
				if (snake->direction == UP) break;
				mtx_lock(mtx);
				new_direction = DOWN;
				mtx_unlock(mtx);
				cnd_signal(cnd);
				break;
			case 'A':
			case 'a':
				if (snake->direction == RIGHT) break;
				mtx_lock(mtx);
				new_direction = LEFT;
				mtx_unlock(mtx);
				cnd_signal(cnd);
				break;
			case EOF:
				if (!atomic_load(game_over)) break;
				return 0;
			default:
				break;
		}
	}
	assert(false);
	return 1;
}
