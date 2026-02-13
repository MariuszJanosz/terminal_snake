#include <stdlib.h>

#include <unistd.h>
#include <termios.h>

#include "terminal.h"

struct termios canonical_terminal;

void save_terminal_settings() {
	if (tcgetattr(STDIN_FILENO, &canonical_terminal) != 0)
		exit(1);
}

void activate_raw_mode() {
	//First set canonical_terminal with save_terminal_settings()
	struct termios raw_terminal = canonical_terminal;
	raw_terminal.c_lflag &= ~ICANON;
	raw_terminal.c_lflag &= ~ECHO;
	
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw_terminal) != 0)
		exit(1);
}

void restore_terminal_settings() {
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &canonical_terminal) != 0)
		exit(1);
}
