#include "shell.h"
#define BUFFER_SIZE 1024
/**
 * ky_execute_command - Forks and executes a command.
 * @cmd_path: Full path to the command to execute.
 * @params: Null-terminated array of parameters for the command.
 *
 * Return: 1 if the command was executed successfully, 0 otherwise.
 */
int ky_execute_command(char *cmd_path, char **params)
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
	return (0);
}
/**
 * ky_handle_command - Constructs the full path to a command and executes it.
 * @dir: Directory where the command is supposed to be located.
 * @params: Null-terminated array of parameters for the command.
 *
 * Return: 1 if the command was executed successfully, -1 otherwise.
 */

int ky_handle_command(char *dir, char **params)
{
	char cmd_path[1024];

	sprintf(cmd_path, "%s/%s", dir, params[0]);

	if (access(cmd_path, F_OK) == 0 && access(cmd_path, X_OK) == 0)
	{
		return (ky_execute_command(cmd_path, params));
	}

	return (-1);
}

/**
 * ky_getline - reads a line from the standard input
 * @line: pointer to a pointer to the line read from the standard input
 * @length: pointer to a size_t for the length of the line
 * @stream: FILE pointer for the input stream
 *
 * Return: the number of bytes read
 */
ssize_t ky_getline(char **line, size_t *length, FILE *stream)
{
	char *buffer = malloc(BUFFER_SIZE);
	ssize_t bytesRead;

	if (buffer == NULL)
	{
		perror("Unable to allocate buffer");
		exit(1);
	}

	bytesRead = getline(line, length, stream);

	free(buffer);

	return (bytesRead);
}

