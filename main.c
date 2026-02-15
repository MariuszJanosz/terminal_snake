#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <threads.h>
#include <stdatomic.h>
#include <assert.h>

#include "board.h"
#include "snake.h"
#include "print_utils.h"
#include "control.h"
#include "terminal.h"

#define difficulty 200000000

int main(int argc, char **argv) {
	save_terminal_settings();
	activate_raw_mode();
	set_cursor_visibility_off();
	non_blocking_input();
	atexit(set_cursor_visibility_on);
	atexit(restore_terminal_settings);
	atexit(remove_non_blocking_input);
	srand(time(NULL));
	Board_t board;
	Snake_t snake;
	init_board(&board, 20, 20);
	init_snake(&snake, &board);
	draw_board(&board);
	fflush(stdout);
	atomic_bool game_over = false;
	mtx_t mtx;
	if (mtx_init(&mtx, mtx_plain) == thrd_error) {
		assert(false && "mtx_init falied!");
		exit(1);
	}
	if (mtx_lock(&mtx) == thrd_error) {
		assert(false && "mtx_lock failed!");
		exit(1);
	}
	cnd_t cnd;
	if (cnd_init(&cnd) != thrd_success) {
		assert(false && "cnd_init failed!");
		exit(1);
	}
	thrd_t thr;
	Control_context_t control_context;
	control_context.snake = &snake;
	control_context.game_over = &game_over;
	control_context.mtx = &mtx;
	control_context.cnd = &cnd;
	struct timespec wake_time;
	if (timespec_get(&wake_time, TIME_UTC) == 0) {
		assert(false && "timespec_get failed!");
		exit(1);
	}
	wake_time.tv_nsec += difficulty;
	if (wake_time.tv_nsec >= 1000000000) {
		wake_time.tv_nsec -= 1000000000;
		wake_time.tv_sec += 1;
	}
	if (cnd_timedwait(&cnd, &mtx, &wake_time) == thrd_error) {
		assert(false && "cnd_timedwait failed!");
		exit(1);
	}
	if (thrd_create(&thr, control, &control_context) != thrd_success) {
		assert(false && "thrd_create failed!");
		exit(1);
	}
	while (!atomic_load(&game_over)) {
		move_snake(&snake, new_direction, &board, &game_over);
		fflush(stdout);
		if (timespec_get(&wake_time, TIME_UTC) == 0) {
			assert(false && "timespec_get failed!");
			exit(1);
		}
		wake_time.tv_nsec += difficulty;
		if (wake_time.tv_nsec >= 1000000000) {
			wake_time.tv_nsec -= 1000000000;
			wake_time.tv_sec += 1;
		}
		if (cnd_timedwait(&cnd, &mtx, &wake_time) == thrd_error) {
			assert(false && "cnd_timedwait failed!");
			exit(1);
		}
	}
	if (thrd_join(thr, NULL) == thrd_error) {
		assert(false && "thrd_join failed!");
		exit(1);
	}
	if (mtx_unlock(&mtx) == thrd_error) {
		assert(false && "mtx_unlock failed!");
		exit(1);
	}
	mtx_destroy(&mtx);
	cnd_destroy(&cnd);
	free_board(&board);
	free_snake(&snake);
	return 0;
}
