#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>
#include <stdio.h>

#include "snake.h"
#include "board.h"
#include "print_utils.h"

void init_snake(Snake_t *snake, Board_t *board) {
	snake->direction = RIGHT;
	snake->growing = false;
	snake->tail = (Snake_segment_t*)malloc(sizeof(*snake->tail));
	if (!snake->tail)
		exit(1);

	assert(board->rows > 2 && board->cols > 2 && "Board is to small!");
	snake->tail->x = board->rows / 2;
	snake->tail->y = board->cols / 2;
	snake->tail->next = NULL;
	board->board[board->cols * snake->tail->x + snake->tail->y] = SNAKE_HEAD_RIGHT;
}

void move_snake(Snake_t *snake, Board_t *board, bool *game_over) {
	assert(snake->tail);
	
	set_table_drawing_on();
	set_color(10, 233, 20);

	if (!snake->growing) {
		board->board[board->cols * snake->tail->x + snake->tail->y] = EMPTY;
		set_cursor_position(snake->tail->x + 1, snake->tail->y + 1);
		printf("%c", cell_state_to_char(
			board->board[board->cols * snake->tail->x + snake->tail->y]));
	}
	else {
		snake->growing = false;
		Snake_segment_t *new_tail = (Snake_segment_t*)malloc(sizeof(*new_tail));
		if (!new_tail)
			exit(1);

		new_tail->x = snake->tail->x;
		new_tail->y = snake->tail->y;
		new_tail->next = snake->tail;
		snake->tail = new_tail;
	}
	Snake_segment_t *it = snake->tail;
	if (it->next && it->x == it->next->x && it->y == it->next->y) {
		board->board[board->cols * it->x + it->y] = SNAKE_SEGMENT;
		set_cursor_position(it->x + 1, it->y + 1);
		printf("%c", cell_state_to_char(
				board->board[board->cols * it->x + it->y]));
		it = it->next;
	}
	while (it->next) {
		it->x = it->next->x;
		it->y = it->next->y;
		it = it->next;
	}

	if (it != snake->tail) {
		board->board[board->cols * it->x + it->y] = SNAKE_SEGMENT;
		set_cursor_position(it->x + 1, it->y + 1);
		printf("%c", cell_state_to_char(
				board->board[board->cols * it->x + it->y]));
	}

	switch (snake->direction) {
		case UP:
			it->x -= 1;
			break;
		case RIGHT:
			it->y += 1;
			break;
		case DOWN:
			it->x += 1;
			break;
		case LEFT:
			it->y -= 1;
			break;
	}

	switch (board->board[board->cols * it->x + it->y]) {
		case WALL:
		case SNAKE_SEGMENT:
			*game_over = true;
	       		break;
		case FOOD:
			snake->growing = true;
			break;
		case EMPTY:
			break;
	}
	
	switch (snake->direction) {
		case UP:
			board->board[board->cols * it->x + it->y] = SNAKE_HEAD_UP;
			break;
		case RIGHT:
			board->board[board->cols * it->x + it->y] = SNAKE_HEAD_RIGHT;
			break;
		case DOWN:
			board->board[board->cols * it->x + it->y] = SNAKE_HEAD_DOWN;
			break;
		case LEFT:
			board->board[board->cols * it->x + it->y] = SNAKE_HEAD_LEFT;
			break;
	}
	set_cursor_position(it->x + 1, it->y + 1);
	printf("%c", cell_state_to_char(
				board->board[board->cols * it->x + it->y]));

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
