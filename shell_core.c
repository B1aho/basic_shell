#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "shell.h"

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

int shell_launch(char **args) {
    pid_t pid, wait_pid;
    int status;

    // Forking the current process 
    pid = fork();
    // After the fork() call, two processes run in parallel from this point: the parent and the child.
    if (pid == 0) {
        // The child process code - init process with new programm (that user want to execute)
        if (execvp(args[0], args)) {
            perror("execute programm fail");
        }
        // If the program execution is successful, execvp() will never return, as the current process is replaced by the new program
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        // If error appear
        perror("fork fail");
    } else {
        // The parent process code - waits for the child process to finish.
        // The system call waitpid() blocks the execution of the current process until the child process 
        // it created either terminates or change state
        do {
            wait_pid = waitpid(wait_pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
    // Child process was finished, return success, so shell could prompt for the next command
    return 1;
}

// Execute command
int shell_execute(char **args) {
  int i;

  if (args[0] == NULL) {
    // An empty command was entered
    return 1;
  }

  // Check if command is builtin
  for (i = 0; i < num_builtins(); i++) {
    if (strcmp(args[0], builtin_str[i]) == 0) {
      return (*builtin_func[i])(args);
    }
  }

  // Execute not builtin program
  return shell_launch(args);
}

/**
 * 1. Read command from standart input - stdin
 * 2. Parse command
 * 3. Execute command
 *  */
void shell_loop(void) {
    char *line;
    char** args;
    int status = 0;
    
    do {
        printf("> ");
        line = read_line();
        args = parse_line(line);
        status = shell_execute(args);
    } while (status);

    free(line);
    free(args);
}