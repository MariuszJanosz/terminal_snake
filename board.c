#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <stdbool.h>

#include "board.h"
#include "print_utils.h"

void init_board(Board_t *board, uint16_t rows, uint16_t cols) {
	board->rows = rows;
	board->cols = cols;
	board->board = (uint8_t*)malloc(rows * cols * sizeof(uint8_t));
	if (!board->board)
		exit(1);
	assert(board->board && "Board allocation failed!");

	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			board->board[cols * i + j] =
				i == 0 		||
				i == rows - 1 	||
				j == 0 		||
				j == cols - 1 	?
				WALL 		:
				EMPTY;
		}
	}
}

char cell_state_to_char(Cell_state_t state) {
	switch (state) {
		case EMPTY:
			return ' ';
		case WALL:
			return 'a';
		case FOOD:
			return '`';
		case SNAKE_SEGMENT:
			return '#';
		case SNAKE_HEAD_UP:
			return 'v';
		case SNAKE_HEAD_RIGHT:
			return '>';
		case SNAKE_HEAD_DOWN:
			return 'w';
		case SNAKE_HEAD_LEFT:
			return '<';
		default:
			assert(false);
			return '\0';
	}
}

void draw_board(Board_t *board) {
	clear_screen();
	set_table_drawing_on();
	set_color(173, 68, 7);
	for (int i = 0; i < board->rows; ++i) {
		for (int j = 0; j < board->cols; ++j) {
			set_cursor_position(i + 1, j + 1);	
			printf("%c",
				cell_state_to_char(
				board->board[board->cols * i + j]));
			
		}
	}
	set_table_drawing_off();
	set_color(255, 255, 255);
}

void free_board(Board_t *board) {
	free(board->board);
}
