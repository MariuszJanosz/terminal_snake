#ifndef BOARD_H
#define BOARD_H

#include <stdint.h>

typedef enum Cell_state_t {
	EMPTY,
	WALL,
	FOOD,
	SNAKE_SEGMENT,
	SNAKE_HEAD_UP,
	SNAKE_HEAD_RIGHT,
	SNAKE_HEAD_DOWN,
	SNAKE_HEAD_LEFT
} Cell_state_t;

typedef struct Board_t {
	uint16_t rows;
	uint16_t cols;
	uint8_t *board; //Cell_state_t
} Board_t;

void init_board(Board_t *board, uint16_t rows, uint16_t cols);
void draw_board(Board_t *board);
void free_board(Board_t *board);

#endif //BOARD_H
