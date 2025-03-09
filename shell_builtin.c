#include "shell.h"
#include <stdio.h>

// List of builtin commands, followed by their corresponding functions.
char *builtin_str[] = {
    "cd",
    "help",
    "exit"
};
  
// List of pointers to builtin functions
int (*builtin_func[]) (char **) = {
    &shell_cd,
    &shell_help,
    &shell_exit
};

int num_builtins(void) {
    return sizeof(builtin_str) / sizeof(char *);
}

// Implements the "cd" command in the shell, which changes the current working directory through chdir system call
int shell_cd(char **args) {
    if (args[1] == NULL) {
        fprintf(stderr, "shell: expected argument to \"cd\"\n");
    } else {
        if (chdir(args[1]) != 0) {
        perror("cd");
        }
    }
    return 1;
}

// Help info about shell functionality
int shell_help(char **args __attribute__((unused))) {

    int i;
    printf("Naive shell implementation\n");
    printf("Type program names and arguments, and hit enter.\n");
    printf("The following are built in:\n");

    for (i = 0; i < num_builtins(); i++) {
        printf("  %s\n", builtin_str[i]);
    }

    printf("Use the man command for information on other programs.\n");
    return 1;
}

// Exit shell
int shell_exit(char **args __attribute__((unused))) {
    return 0;
}