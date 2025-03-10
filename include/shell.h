#ifndef SHELL_H
#define SHELL_H

#include <unistd.h>
#define ARGS_SIZE 40
#define SPACE " \t\r\n\a"
#define LINE_BUFF_SIZE 1024
#define GREEN "\033[1;32m"
#define BLUE "\033[1;34m"
#define RESET_COLOR "\033[0m"

void shell_loop(void);
/*
  Function Declarations for builtin shell commands:
 */
int shell_help(char **args);
int shell_cd(char **args);
int shell_exit(char **args);
int num_builtins(void);

extern char *builtin_str[];
extern int (*builtin_func[])(char **);

typedef struct packInfo{
  const char *suggestion;
  const char *pmn;
} PackageInfo;

typedef struct {
    const char *path;
    PackageInfo packageInfo;
} PackageManager;

#endif 