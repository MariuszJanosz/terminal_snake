#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <threads.h>

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
	atexit(restore_terminal_settings);
	set_cursor_visibility_off();
	atexit(set_cursor_visibility_on);
	srand(time(NULL));
	Board_t board;
	Snake_t snake;
	init_board(&board, 20, 20);
	init_snake(&snake, &board);
	draw_board(&board);
	fflush(stdout);
	thrd_t thr;
	thrd_create(&thr, control, &snake);
	thrd_detach(thr);
	thrd_sleep(&difficulty, &rem);
	bool game_over = false;
	while (!game_over) {
		move_snake(&snake, new_direction, &board, &game_over);
		fflush(stdout);
		thrd_sleep(&difficulty, &rem);
	}
	free_board(&board);
	free_snake(&snake);
	return 0;
}
