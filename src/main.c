#include <stdlib.h>
#include <time.h>

#include "renderer.h"

char exit_flag = 1;

void handle_input(int ch) {
    switch (ch) {
        case 'q':
            exit_flag = 0;
            break;
        case ' ':
            wipe();
        default:
            break;
    }
}

void randomize() {
    srand(time(NULL));
}

int main() {
    randomize();

    setup();

    struct timespec down_cycle = {0, 10000000};

    while(exit_flag) {
        render();

        handle_input(take_input());
        nanosleep(&down_cycle, NULL);
    }

    finish();

    return EXIT_SUCCESS;
}
