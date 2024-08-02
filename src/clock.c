#include <time.h>

#include "clock.h"

static unsigned long current_time;

long get_current_time() {
    return current_time;
}

void set_current_time(unsigned long time) {
    current_time = time;
}

void increment_current_time() {
    current_time++;
}
