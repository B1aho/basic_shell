#include <stdlib.h>
#include <stdio.h>
#include "include/shell.h"

int main(void) {
    // Run command loop
    shell_loop();
    // Perform any shutdown/cleanup
    exit(EXIT_SUCCESS);
}
