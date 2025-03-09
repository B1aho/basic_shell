#ifndef SHELL_H
#define SHELL_H

#define ARGS_SIZE 40
#define SPACE " \t\r\n\a"
#define LINE_BUFF_SIZE 1024

void shell_loop(void);
/*
  Function Declarations for builtin shell commands:
 */
int shell_help(char **args);
int shell_cd(char **args);
int shell_exit(char **args);

#endif 