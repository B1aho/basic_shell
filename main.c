#include <stdio.h>
#include <stdlib.h>

void is_buff_error(char *buff) {
    if (!buff) {
        fprintf(stderr, "Error: can't allocate buffer for line");
        exit(EXIT_FAILURE);
    }
}
// Read all user command line from stdin 
#define LINE_BUFF_SIZE 1024
char *read_line() {
    int buff_idx = 0;
    int buff_size = LINE_BUFF_SIZE;
    char* buffer = (char *)malloc(sizeof(char) * buff_size);
    is_buff_error(buffer);
    // Process all chars from line
    int ch;
    while (1) {
        ch = getchar();
        // If end of the line - return line
        if (ch == EOF || ch == '\n') {
            buffer[buff_idx] = '\0';
            return buffer;
        } else {
            buffer[buff_idx++] = ch;
        }

        // Suddenly, line is bigger then buffer
        if (buff_idx >= buff_size) {
            buff_size += LINE_BUFF_SIZE;
            buffer = realloc(buffer, buff_size);
            is_buff_error(buffer);
        }
    }
}
/**
 * 1. Read command from standart input - stdin
 * 2. Parse command
 * 3. Execute command
 *  */
void shell_loop(void) {
    char *line;
    char** args;
    int status;
    
    do {
        printf("> ");
        line = read_line();
        //args = parse_line(line);
        //status = execute_command(args);
    } while (status);

    free(line);
    free(args);
}


int main(void) {
    // Load config.

    // Run command loop.
    shell_loop();
    // Clear stdin

    // Perform any shutdown/cleanup.
    exit(EXIT_SUCCESS);
}
