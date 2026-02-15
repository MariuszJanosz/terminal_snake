#ifndef TERMINAL_H
#define TERMINAL_H

#include <stdint.h>

#include <termios.h>

extern struct termios *canonical_terminal;

void save_terminal_settings();
void activate_raw_mode();
void restore_terminal_settings();
void non_blocking_input();
void remove_non_blocking_input();
void get_terminal_size(uint16_t *rows, uint16_t *cols);

#endif //TERMINAL_H
