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
	assert(board->board && "Board allocation failed!");
	if (!board->board)
		exit(1);

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

void cell_state_to_rgb(Cell_state_t state, uint8_t *r, uint8_t *g, uint8_t *b) {
	switch (state) {
		case WALL:
			*r = 173;
			*g = 68;
			*b = 7;
			break;
		case FOOD:
			*r = 240;
			*g = 20;
			*b = 15;
			break;
		case SNAKE_SEGMENT:
		case SNAKE_HEAD_UP:
		case SNAKE_HEAD_RIGHT:
		case SNAKE_HEAD_DOWN:
		case SNAKE_HEAD_LEFT:
			*r = 0;
			*g = 222;
			*b = 33;
			break;
		case EMPTY:
		default:
			*r = *g = *b = 0;
			break;
	}
}

void draw_board(Board_t *board) {
	clear_screen();
	set_table_drawing_on();
	for (int i = 0; i < board->rows; ++i) {
		for (int j = 0; j < board->cols; ++j) {
			Cell_state_t state = board->board[board->cols * i + j];
			char c = cell_state_to_char(state);
			uint16_t row = i + 1;
			uint16_t col = j + 1;
			uint8_t r, g, b;
			cell_state_to_rgb(state, &r, &g, &b);
			print_char(c, row, col, r, g, b);
		}
	}
	set_table_drawing_off();
	set_color(255, 255, 255);
}

void free_board(Board_t *board) {
	free(board->board);
}
