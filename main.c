#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

#include "board.h"
#include "snake.h"

int main(int argc, char **argv) {
	Board_t board;
	Snake_t snake;
	init_board(&board, 20, 50);	
	init_snake(&snake, &board);
	draw_board(&board);
	getchar();
	bool game_over = false;
	while (!game_over) {
		move_snake(&snake, &board, &game_over);
		getchar();
	}
	free_board(&board);
	free_snake(&snake);
	return 0;
}
