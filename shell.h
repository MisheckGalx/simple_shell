#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_NUM_ARGS 10

/* Function Prototypes */
void ky_parse_cmd(char *cmd, char **params);
int  ky_execute_cmd(char **params);

#endif /* SHELL_H */
