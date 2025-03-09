#include <stdlib.h>
#include "shell.h"

int main(void) {
    // Load config.

    // Run command loop.
    shell_loop();
    // Clear stdin

    // Perform any shutdown/cleanup.
    exit(EXIT_SUCCESS);
}
