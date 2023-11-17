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
 * ky_execute_cmd - a function that executes the command
 * @params: parameters for the command
 *
 * Return: 1 on success, 0 on failure
 */
int ky_execute_cmd(char **params)
{
	if (strcmp(params[0], "env") == 0)
	{
		char **env = environ;

		while (*env != NULL)
		{
			printf("%s\n", *env);
			env++;
		}
		return (1);
	}
	if (params[0][0] == '/')
	{
		if (access(params[0], F_OK) == 0 && access(params[0], X_OK) == 0)
		{
			return (ky_execute_command(params[0], params));
		}
		else
		{
			printf("shell: %s: command not found\n", params[0]);
			return (0);
		}
	}
	else
	{
		char *path = getenv("PATH");
		char *path_copy = strdup(path);
		char *dir = strtok(path_copy, ":");

		while (dir != NULL)
		{
			int result = ky_handle_command(dir, params);

			if (result != -1)
				return (result);
			dir = strtok(NULL, ":");
		}
		printf("shell: %s: command not found\n", params[0]);
		return (0);
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

		bytesRead = getline(&cmd, &cmdLength, stdin);
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
