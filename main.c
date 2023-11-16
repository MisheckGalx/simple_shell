#include "shell.h"
/**
 * ky_pr - Prints the shell prompt
 * @void: No arguments
 *
 * Return: Void
 */
void ky_pr(void)
{
	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "$ ", 2);
}
/**
 * ky_ex - Executes the command entered by the user
 * @line: The command entered by the user
 *
 * Return: Void
 */
void ky_ex(char *line)
{
	char **argv;
	char *command;

	line[ky_strcspn(line, "\n")] = '\0';

	line = ky_tr_spaces(line);

	if (ky_strlen(line) == 0)
	{
		return;
	}
	argv = ky_tokenize(line);
	if (ky_exit(argv))
	{
		free(line);
		exit(EXIT_SUCCESS);
	}
	if (ky_env(argv))
	{
		free(argv);
		return;
	}
	command = ky_find_command(argv);
	if (command == NULL)
	{
		write(STDOUT_FILENO, argv[0], ky_strlen(argv[0]));
		write(STDOUT_FILENO, ": command not found\n", 20);
		free(argv);
		free(line);
		return;
	}
	argv[0] = command;
	ky_execute(argv);
	free(command);
	free(argv);
	free(line);
}

/**
 * main - Entry point of the program
 * @void: No arguments
 *
 * Return: 0 if success, 1 otherwise
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;

	while (1)
	{
		ky_pr();
		read = getline(&line, &len, stdin);
		if (read == -1) /* End of the file (Ctrl+D) */
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			exit(EXIT_SUCCESS);
		}
		ky_ex(line);

	}
	return (0);
}

/**
 * ky_tr_spaces - function removes trailing from cli
 * @str: strings
 * Return: character
 */
char *ky_tr_spaces(char *str)
{
	char *end;

	/* Remove leading spaces */
	while (isspace((unsigned char)*str))
		str++;

	/* Remove trailing spaces */
	end = str + strlen(str) - 1;
	while (end > str && isspace((unsigned char)*end))
		end--;

	/* Write new null terminator */
	*(end + 1) = '\0';

	return (str);
}
