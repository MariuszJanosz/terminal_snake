#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <threads.h>
#include <stdatomic.h>

#include "board.h"
#include "snake.h"
#include "print_utils.h"
#include "control.h"
#include "terminal.h"

const struct timespec difficulty = {0, 350000000};
struct timespec rem = {0, 0};

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
	thrd_t thr;
	Control_context_t control_context;
	control_context.snake = &snake;
	control_context.game_over = &game_over;
	thrd_create(&thr, control, &control_context);
	thrd_sleep(&difficulty, &rem);
	while (!atomic_load(&game_over)) {
		move_snake(&snake, new_direction, &board, &game_over);
		fflush(stdout);
		thrd_sleep(&difficulty, &rem);
	}
	thrd_join(thr, NULL);
	free_board(&board);
	free_snake(&snake);
	return 0;
}
