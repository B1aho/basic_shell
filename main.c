#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Check if buffer allocated with error
void is_buff_error(void *ptr) {
    if (!ptr) {
        fprintf(stderr, "Error: can't allocate buffer");
        exit(EXIT_FAILURE);
    }
}

void print_args(char **args) {
    int pos = 0;
    while (args[pos] != NULL) {
        printf("%d)arg - %s\n", pos + 1, args[pos]);
        pos++;
    }
    return;
}

// Parse line by spaces
#define ARGS_SIZE 40
#define SPACE " \t\r\n\a"
char **parse_line(char *line) {
    int args_size = ARGS_SIZE, position = 0;
    char **args = malloc(sizeof(char *) * args_size);
    is_buff_error(args);
    // The function returns lexemes from the string and replaces delimiters with \0
    char *token = strtok(line, SPACE);
    while (token != NULL) {
        args[position++] = token;

        if (position >= args_size) {
            args_size += ARGS_SIZE;
            args = realloc(args, args_size * sizeof(char *));
            is_buff_error(args);
        }
        token = strtok(NULL, SPACE);
    }
    args[position] = NULL;
    return args;
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
        args = parse_line(line);
        print_args(args);
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
