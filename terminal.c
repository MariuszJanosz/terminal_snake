#include <stdlib.h>
#include <assert.h>
#include <stdint.h>
#include <stdbool.h>

#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <sys/ioctl.h>

#include "terminal.h"

struct termios *canonical_terminal = NULL;
struct termios __canonical_terminal;

void save_terminal_settings() {
	if (tcgetattr(STDIN_FILENO, &__canonical_terminal) != 0) {
		assert(false && "save_terminal_settings failed!");
		exit(1);
	}
	canonical_terminal = &__canonical_terminal;
}

void activate_raw_mode() {
	//First set canonical_terminal with save_terminal_settings()
	assert(canonical_terminal &&
		"First set canonical_terminal with save_terminal_settings()");
	struct termios raw_terminal = *canonical_terminal;
	raw_terminal.c_lflag &= ~ICANON;
	raw_terminal.c_lflag &= ~ECHO;

	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw_terminal) != 0) {
		assert(false && "activate_raw_mode failed!");
		exit(1);
	}
}

void restore_terminal_settings() {
	assert(canonical_terminal && "restore_terminal_settings failed, no canonical_terminal set!");
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, canonical_terminal) != 0) {
		assert(false && "restore_terminal_settings failed!");
		exit(1);
	}
}

void non_blocking_input() {
	int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
	if (flags == -1) {
		assert(false && "non_blocking_input failed, getting flags failed!");
		exit(1);
	}
	int res = fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);
	if (res == -1) {
		assert(false && "non_blocking_input failed, setting flags failed!");
		exit(1);
	}
}

void remove_non_blocking_input() {
	int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
	if (flags == -1) {
		assert(false && "remove_non_blocking_input failed, getting flags failed!");
		exit(1);
	}
	int res = fcntl(STDIN_FILENO, F_SETFL, flags & ~O_NONBLOCK);
	if (res == -1) {
		assert(false && "remove_non_blocking_input failed, setting flags failed!");
		exit(1);
	}
}

void get_terminal_size(uint16_t *rows, uint16_t *cols) {
	struct winsize tmp;
	int res = ioctl(0, TIOCGWINSZ, &tmp);
	if (res == -1) {
		assert(false && "get_terminal_size failed!");
		exit(1);
	}
	*rows = tmp.ws_row;
	*cols = tmp.ws_col;
}
