#include "shell.h"

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
	int i;

	for (i = 0; i < MAX_NUM_ARGS; i++)
	{
		params[i] = strsep(&cmd, " ");

		if (params[i] == NULL)
			break;
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
	pid_t pid = fork();

	if (pid < 0)
	{
		perror("fork");
		return (1);
	}
	else if (pid == 0)
	{
		execve(params[0], params, NULL);
		perror(params[0]);
		return (0);
	}
	else
	{
		int childStatus;

		waitpid(pid, &childStatus, 0);
		return (1);
	}
}

/**
 * main - main function for the shell
 *
 * Return: 0 on success
 */
int main(void)
{
	char *cmd = NULL;
	char *params[MAX_NUM_ARGS];
	size_t cmdLength = 0;
	ssize_t bytesRead;

	while (1)
	{
		write(STDOUT_FILENO, "$ ", 2);

		bytesRead = getline(&cmd, &cmdLength, stdin);
		if (bytesRead == -1)
			break;
		if (cmd[0] == '\n')
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
