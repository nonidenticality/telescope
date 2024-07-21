#include <stdlib.h>
#include <time.h>

#include "stars.h"

char exit_flag = 1;

void handle_input(View* view, int ch) {
    switch (ch) {
        case 'q':
            exit_flag = 0;
            break;
        case ' ':
            view->seed = rand();
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
    View view = {(long)rand()};

    setup();

    struct timespec down_cycle = {0, 10000000};

    while(exit_flag) {
        render(&view);

        handle_input(&view, take_input());
        nanosleep(&down_cycle, NULL);
    }

    finish();

    return EXIT_SUCCESS;
}
