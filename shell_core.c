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
        printf("%d) - %s\n", pos + 1, args[pos]);
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
    char is_quote_arg = 0;
    while (token != NULL) {
        // Parse quoted string as one whole argument
        if (token[0] == '"') {
            char *arg = malloc(strlen(token) + 2);
            token++;
            strcpy(arg, token);
            arg[strlen(token)] = ' ';
            // Find next part with closing quote
            while (1) {
                token = strtok(NULL, "\"");
                if (token == NULL)
                    break;
                char *temp = malloc(strlen(arg) + strlen(token) + 2);
                sprintf(temp, "%s %s", arg, token);
                free(arg);
                arg = temp;
                break;
            }
            args[position++] = arg;
            is_quote_arg = 1;
        }

        if (!is_quote_arg)
            args[position++] = token;

        is_quote_arg = 0;

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

        // If, suddenly, line is bigger then buffer
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

// Get current working directory
char *get_cwd(void) {
    char *cwd = getcwd(NULL, 0);
    if (!cwd) {
        perror("getcwd");
        return NULL;
    }
    // Get home directory
    char *home = getenv("HOME"); 
    char *shorter_cwd = NULL;
    if (home && strncmp(cwd, home, strlen(home)) == 0) {
        // Change home in cwd with ~
        shorter_cwd = (char *)malloc(sizeof(char) * (strlen(cwd) - strlen(home) + 2));
        shorter_cwd[0] = '~';
        strcpy(&shorter_cwd[1], &cwd[strlen(home)]);
        free(cwd);
    }
    return shorter_cwd;
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
    char *cwd = get_cwd();
    if (cwd == NULL) {
        return;
    }
    do {
        printf("%s> ", cwd);
        line = read_line();
        args = parse_line(line);
        print_args(args);
        status = shell_execute(args);
        // Update cwd if working directory changed
        if (args[0] && !strncmp(args[0], "cd", 2)) {
            free(cwd);
            cwd = get_cwd();
        }
    } while (status);

    free(line);
    free(args);
    free(cwd);
}