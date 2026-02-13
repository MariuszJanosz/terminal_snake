#ifndef CONTROL_H
#define CONTROL_H

#include <stdatomic.h>

#include "snake.h"

typedef struct Control_context_t {
	Snake_t *snake;
	atomic_bool *game_over;
} Control_context_t;

extern Direction_t new_direction;

int control(void *context);

#endif //CONTROL_H
