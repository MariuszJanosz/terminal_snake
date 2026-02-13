#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>
#include <stdio.h>
#include <stdatomic.h>

#include "snake.h"
#include "board.h"
#include "print_utils.h"

void init_snake(Snake_t *snake, Board_t *board) {
	snake->direction = RIGHT;
	snake->growing = false;
	snake->tail = (Snake_segment_t*)malloc(sizeof(*snake->tail));
	if (!snake->tail)
		exit(1);

	assert(board->rows > 2 && board->cols > 5 && "Board is to small!");
	snake->tail->row = board->rows / 2;
	snake->tail->col = board->cols / 2;
	snake->tail->next = NULL;
	board->board[board->cols * snake->tail->row + snake->tail->col] = SNAKE_HEAD_RIGHT;
}

void move_snake(Snake_t *snake, Direction_t new_direction, Board_t *board, atomic_bool *game_over) {
	assert(snake->tail);
	
	snake->direction = new_direction;

	set_table_drawing_on();
	set_color(10, 233, 20);

	if (!snake->growing) {
		board->board[board->cols * snake->tail->row + snake->tail->col] = EMPTY;
		set_cursor_position(snake->tail->row + 1, snake->tail->col + 1);
		printf("%c", cell_state_to_char(
			board->board[board->cols * snake->tail->row + snake->tail->col]));
	}
	else {
		snake->growing = false;
		Snake_segment_t *new_tail = (Snake_segment_t*)malloc(sizeof(*new_tail));
		if (!new_tail)
			exit(1);

		new_tail->row = snake->tail->row;
		new_tail->col = snake->tail->col;
		new_tail->next = snake->tail;
		snake->tail = new_tail;
	}
	Snake_segment_t *it = snake->tail;
	if (it->next && it->row == it->next->row && it->col == it->next->col) {
		board->board[board->cols * it->row + it->col] = SNAKE_SEGMENT;
		set_cursor_position(it->row + 1, it->col + 1);
		printf("%c", cell_state_to_char(
				board->board[board->cols * it->row + it->col]));
		it = it->next;
	}
	while (it->next) {
		it->row = it->next->row;
		it->col = it->next->col;
		it = it->next;
	}

	if (it != snake->tail) {
		board->board[board->cols * it->row + it->col] = SNAKE_SEGMENT;
		set_cursor_position(it->row + 1, it->col + 1);
		printf("%c", cell_state_to_char(
				board->board[board->cols * it->row + it->col]));
	}

	switch (snake->direction) {
		case UP:
			it->row -= 1;
			break;
		case RIGHT:
			it->col += 1;
			break;
		case DOWN:
			it->row += 1;
			break;
		case LEFT:
			it->col -= 1;
			break;
	}

	switch (board->board[board->cols * it->row + it->col]) {
		case WALL:
		case SNAKE_SEGMENT:
			atomic_store(game_over, true);
	       		break;
		case FOOD:
			snake->growing = true;
			{
				uint16_t frow, fcol;
				while (true) {
					frow = rand() % board->rows;
					fcol = rand() % board->cols;
					if (board->board[board->cols * frow 
							+ fcol] == EMPTY) {
						board->board[board->cols * frow
							+ fcol] = FOOD;
						uint8_t r, g, b;
						cell_state_to_rgb(FOOD, &r, &g, &b);
						print_char(cell_state_to_char(FOOD),
								frow + 1, fcol + 1,
								r, g, b);
						break;
					}
				}
			}
			break;
		case EMPTY:
			break;
	}
	
	switch (snake->direction) {
		case UP:
			board->board[board->cols * it->row + it->col] = SNAKE_HEAD_UP;
			break;
		case RIGHT:
			board->board[board->cols * it->row + it->col] = SNAKE_HEAD_RIGHT;
			break;
		case DOWN:
			board->board[board->cols * it->row + it->col] = SNAKE_HEAD_DOWN;
			break;
		case LEFT:
			board->board[board->cols * it->row + it->col] = SNAKE_HEAD_LEFT;
			break;
	}
	uint8_t r, g, b;
	cell_state_to_rgb(board->board[board->cols * it->row + it->col], &r, &g, &b);
	print_char(cell_state_to_char(board->board[board->cols * it->row + it->col]),
			it->row + 1, it->col + 1,
			r, g, b);

	set_table_drawing_off();
	set_color(255, 255, 255);
}

void free_snake(Snake_t *snake) {
	Snake_segment_t *it = snake->tail;
	while (it) {
	Snake_segment_t *to_free = it;
	it = it->next;
	free(to_free);
	}
}
