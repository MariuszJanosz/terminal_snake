#ifndef TERMINAL_H
#define TERMINAL_H

#include <termios.h>

extern struct termios canonical_terminal;

void save_terminal_settings();
void activate_raw_mode();
void restore_terminal_settings();

#endif //TERMINAL_H
