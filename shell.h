#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_NUM_ARGS 10
extern char **environ;

/* Function Prototypes */
void ky_parse_cmd(char *cmd, char **params);
int  ky_execute_cmd(char **params);
int ky_handle_command(char *dir, char **params);
int ky_execute_command(char *cmd_path, char **params);
ssize_t ky_getline(char **line, size_t *length, FILE *stream);
#endif /* SHELL_H */
