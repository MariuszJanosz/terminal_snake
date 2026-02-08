#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <assert.h>

#include "board.h"

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

void draw_board(Board_t *board) {
	printf("\x1b[2J"); //Clear screen
	printf("\x1b[3J"); //Delete scroll-back buffer
	printf("\x1b[38;5;135m"); //Set color to light purple
	printf("\x1b(0"); //Enter table drawing mode
	for (int i = 0; i < board->rows; ++i) {
		for (int j = 0; j < board->cols; ++j) {
			//Move cursor to (i + 1)-st row (j + 1)-st col
			printf("\x1b[%d;%dH", i + 1, j + 1);
			switch (board->board[board->cols * i + j]) {
				case WALL: //Print block
					printf("a");
					break;
				case EMPTY:
					printf(" ");
					break;
				case FOOD: //Print diamond
					printf("`");
					break;
				case SNAKE_SEGMENT:
					printf("#");
					break;
				case SNAKE_HEAD_UP: //Print arrow up
					printf("v");
					break;
				case SNAKE_HEAD_RIGHT:
					printf(">");
					break;
				case SNAKE_HEAD_DOWN: //Print arrow down
					printf("w");
					break;
				case SNAKE_HEAD_LEFT:
					printf("<");
					break;
				default:
			}
		}
	}
	printf("\x1b(B"); //Return from table drawing mode
	printf("\x1b[0m"); //Set color to normal
}

void free_board(Board_t *board) {
	free(board->board);
}
