#include <stdio.h>

#include "print_utils.h"

void clear_screen() {
	printf("\x1b[2J"); //Clear screen
	printf("\x1b[3J"); //Delete scroll-back buffer
}

void set_table_drawing_on() {
	printf("\x1b(0");
}

void set_table_drawing_off() {
	printf("\x1b(B");
}

void set_color(uint8_t r, uint8_t g, uint8_t b) {
	printf("\x1b[38;2;%d;%d;%dm", r, g, b);
}

void set_cursor_position(uint16_t row, uint16_t col) {
	printf("\x1b[%d;%dH", row, col);
}

void set_cursor_visibility_on() {
	printf("\x1b[?25h");
}

void set_cursor_visibility_off() {
	printf("\x1b[?25l");
}

void set_blinking_on() {
	printf("\x1b[5m");
}
void set_blinking_off() {
	printf("\x1b[25m");
}

void set_bold_on() {
	printf("\x1b[1m");
}

void set_bold_off() {
	printf("\x1b[22m");
}
