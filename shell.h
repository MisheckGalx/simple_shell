#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/stat.h>

#define DELIM " \t\n"


/******************Major functions****************/
int main(int argc, char **argv);
ssize_t ky_write(int fd, const void *buffer, size_t count);
char *ky_rd_input(void);
int ky_x_cmd(char **token, char **argv);
void sigint_handler(int signum);
size_t ky_cnt_tkn(char *str);
char **ky_input_pasr(char *input);
int ky_execute_command(char *cmd, char **tokens, char **argv);
char *ky_find_executable(char **tokens, char **argv);
char *ky_check_builtins(char **tokens);
int ky_x_cmd(char **tokens, char **argv);


#endif /* SHELL_H */
