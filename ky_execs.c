#include "shell.h"

/**
 * ky_tokenize - Tokenizes the line into an array of strings
 * @line: The command line
 *
 * Return: An array of strings
 */
char **ky_tokenize(char *line)
{
	char **argv = malloc(64 * sizeof(char *));
	char *copy_line = ky_strdup(line);

	char *token = strtok(copy_line, " \"");
	int i;

	for (i = 0; token != NULL; i++)
	{
		argv[i] = ky_strdup(token);
		token = strtok(NULL, " \"");
	}
	argv[i] = NULL;

	free(copy_line);
	return (argv);
}

/**
 * ky_find_command - Finds the command in the current directory or PATH
 * @argv: The array of command and arguments
 *
 * Return: The full path to the command or NULL if command not found
 */
char *ky_find_command(char **argv)
{
	/* Check if command is an absolute path */
	if (argv[0][0] == '/')
	{
		if (access(argv[0], F_OK) != -1)
		{
			/* Command found */
			return (ky_strdup(argv[0]));
		}
		else
		{
			free(argv);
			return (NULL);
		}
	}

	/* Check if command exists in current directory or PATH */
	if (access(argv[0], F_OK) == -1)
	{
		char *path = getenv("PATH");
		char *path_copy = ky_strdup(path);
		char *directory = ky_strtok(path_copy, ":");

		while (directory != NULL)
		{
			char *command_path = malloc(strlen(directory) +
					strlen(argv[0]) + 2);
			ky_strcpy(command_path, directory);
			ky_strcat(command_path, "/");
			ky_strcat(command_path, argv[0]);
			if (access(command_path, F_OK) != -1)
			{
				free(path_copy);
				return (command_path);
			}
			free(command_path);
			directory = ky_strtok(NULL, ":");
		}
		free(path_copy);
	}
	return (NULL);
}

/**
 * ky_execute - Executes the command
 * @argv: The array of command and arguments
 *
 * Return: Void
 */
void ky_execute(char **argv)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == 0) /* Child process */
	{
		if (execvp(argv[0], argv) == -1)
		{
			perror(argv[0]);
		}
		exit(0);
	}
	else if (pid < 0) /* Error forking */
	{
		perror(argv[0]);
	}
	else /* Parent process */
	{
		do {
			waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
}

/**
 * ky_exit - Exit the shell
 * @argv: The command and its arguments
 *
 * Return: 1 if the shell should exit, 0 otherwise
 */
int ky_exit(char **argv)
{
	if (argv[0] != NULL && ky_strcmp(argv[0], "exit") == 0)
	{
		return (1);
	}
	return (0);
}

/**
 * ky_env - Print the current environment
 * @argv: The command and its arguments
 *
 * Return: 1 if the shell should print the environment, 0 otherwise
 */
int ky_env(char **argv)
{
	int i;

	if (argv[0] != NULL && ky_strcmp(argv[0], "env") == 0)
	{
		for (i = 0; environ[i] != NULL; i++)
		{
			write(STDOUT_FILENO, environ[i], ky_strlen(environ[i]));
			write(STDOUT_FILENO, "\n", 1);
		}
		return (1);
	}
	return (0);
}
