#include <time.h>

#include "clock.h"

long get_current_time() {
    return time(NULL);
}

uint64_t get_current_nanoseconds() {
    struct timespec ts;

    if (timespec_get(&ts, TIME_UTC) != TIME_UTC) {
        return 0;
    }

    return 1000000000 * ts.tv_sec + ts.tv_nsec;
}

