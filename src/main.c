#include <stdlib.h>

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

int main() {
    View view = {(long)rand(), 5, 5};

    setup();

    while(exit_flag) {
        render(&view);

        handle_input(&view, take_input());
    }

    finish();

    return EXIT_SUCCESS;
}
