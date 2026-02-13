#include <stdlib.h>
#include <assert.h>

#include <unistd.h>
#include <termios.h>
#include <fcntl.h>

#include "terminal.h"

struct termios *canonical_terminal = NULL;
struct termios __canonical_terminal;

void save_terminal_settings() {
	if (tcgetattr(STDIN_FILENO, &__canonical_terminal) != 0)
		exit(1);
	canonical_terminal = &__canonical_terminal;
}

void activate_raw_mode() {
	//First set canonical_terminal with save_terminal_settings()
	assert(canonical_terminal &&
		"First set canonical_terminal with save_terminal_settings()");
	struct termios raw_terminal = *canonical_terminal;
	raw_terminal.c_lflag &= ~ICANON;
	raw_terminal.c_lflag &= ~ECHO;

	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw_terminal) != 0)
		exit(1);
}

void restore_terminal_settings() {
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, canonical_terminal) != 0)
		exit(1);
}

void non_blocking_input() {
	int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
	fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);
}

void remove_non_blocking_input() {
	int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
	fcntl(STDIN_FILENO, F_SETFL, flags & ~O_NONBLOCK);
}
