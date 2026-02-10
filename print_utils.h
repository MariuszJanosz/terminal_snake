#ifndef PRINT_UTILS_H
#define PRINT_UTILS_H

#include <stdint.h>

void clear_screen();
void set_table_drawing_on();
void set_table_drawing_off();
void set_color(uint8_t r, uint8_t g, uint8_t b);
void set_cursor_position(uint16_t row, uint16_t col);
void set_cursor_visibility_on();
void set_cursor_visibility_off();
void set_blinking_on();
void set_blinking_off();
void set_bold_on();
void set_bold_off();
void print_char(char c, uint16_t row, uint16_t col, uint8_t r, uint8_t g, uint8_t b);

#endif //PRINT_UTILS_H

