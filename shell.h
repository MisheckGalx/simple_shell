#ifndef SHELL_H
#define SHELL_H

extern char **environ;

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

/****FUNCTIONS******/

void ky_pr(void);
char **ky_tokenize(char *line);
char *ky_find_command(char **argv);
void ky_execute(char **argv);
void ky_ex(char *line);
int main(void);
int ky_exit(char **argv);
int ky_env(char **argv);

/****CUSTOM STRINGS*****/

char *ky_strcpy(char *dest, const char *src);
char *ky_strcat(char *dest, const char *src);
int ky_strcmp(const char *s1, const char *s2);
size_t ky_strcspn(const char *str1, const char *str2);
ssize_t ky_getline(char **lineptr, size_t *n, FILE *stream);
size_t ky_strlen(const char *s);
char *ky_strtok(char *str, const char *delim);
char *ky_strdup(const char *s);

#endif /* SHELL_H */
