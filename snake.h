#ifndef SNAKE_H
#define SNAKE_H

#include <stdint.h>
#include <stdbool.h>

#include "board.h"

typedef enum Direction_t {
	UP,
	RIGHT,
	DOWN,
	LEFT
} Direction_t;

typedef struct Snake_segment_t {
	struct Snake_segment_t *next;
	uint16_t row;
	uint16_t col;
} Snake_segment_t;

typedef struct Snake_t {
	Snake_segment_t *tail;
	Direction_t direction;
	bool growing;
} Snake_t;

void init_snake(Snake_t *snake, Board_t *board);
void move_snake(Snake_t *snake, Board_t *board, bool *game_over);
void free_snake(Snake_t *snake);

#endif //SNAKE_H
