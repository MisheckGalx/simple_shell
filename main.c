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
	char *path = getenv("PATH");
	char *path_copy = strdup(path);
	char *dir = strtok(path_copy, ":");

	while (dir != NULL)
	{
		char cmd_path[1024];

		sprintf(cmd_path, "%s/%s", dir, params[0]);

		if (access(cmd_path, F_OK) == 0 && access(cmd_path, X_OK) == 0)
		{
			pid_t pid = fork();

			if (pid < 0)
			{
				perror("fork");
				return (1);
			}
			else if (pid == 0)
			{
				if (execve(cmd_path, params, NULL) == -1)
				{
					perror(params[0]);
					exit(0);
				}
			}
			else
			{
				int childStatus;

				waitpid(pid, &childStatus, 0);
				return (1);
			}
		}

		dir = strtok(NULL, ":");
	}

	printf("shell: %s: command not found\n", params[0]);
	return (0);
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
