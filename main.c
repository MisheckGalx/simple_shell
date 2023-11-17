#include "shell.h"
#include <unistd.h>
#define MAX_NUM_ARGS 10

/**
 * ky_parse_cmd - a function that parses the command
 * @cmd: the command
 * @params: parameters for the command
 *
 * Return: nothing
 */
void ky_parse_cmd(char *cmd, char **params)
{
	int i = 0;

	/* split command into separate strings */
	params[i] = strtok(cmd, " ");

	while (params[i] != NULL)
	{
		i++;
		params[i] = strtok(NULL, " ");
	}
}

/**
 * main - Entry point
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
	char *cmd = NULL;
	char *params[MAX_NUM_ARGS];
	size_t cmdLength = 0;
	ssize_t bytesRead;
	int interactive = isatty(0);

	while (1)
	{
		if (interactive)
			write(STDOUT_FILENO, "$ ", 2);

		bytesRead = ky_getline(&cmd, &cmdLength, stdin);

		if (bytesRead == -1)
			break;
		if (cmd[0] == '\n') /* If input is only a newline, continue */
			continue;
		cmd[bytesRead - 1] = '\0';
		ky_parse_cmd(cmd, params);

		if (strcmp(params[0], "exit") == 0)
			break;
		if (ky_execute_cmd(params) == 0)
			break;
	}
	free(cmd);
	return (0);
}
