#include "shell.h"
/**
 * main - Entry point
 * @argc: The num of args
 * @argv: array
 * Return: 0 if success, 1 otherwise
 */
int main(int argc, char **argv)
{
	char *input, **tokens;
	int stat;

	(void)argc;
	signal(SIGINT, sigint_handler);
	stat = 1;

	while (stat)
	{
		if (isatty(STDIN_FILENO))
			ky_write(STDOUT_FILENO, "$ ", 2);

		input = ky_rd_input();
		if (input == NULL)
		{
			ky_write(STDOUT_FILENO, "\n", 1);
			break;
		}
		tokens = ky_input_pasr(input);
		if (tokens == NULL)
		{
			free(input);
			continue;
		}

		stat = ky_x_cmd(tokens, argv);
		free(input);
		free(tokens);
	}
	return (0);
}

/**
 * ky_x_cmd - Exe cmds
 * @tokens: array of toks
 * @argv: array
 * Return: 1 if sucess, 0 if exit, -1 if error
 */

int ky_x_cmd(char **tokens, char **argv)
{
	char *cmd;

	if (tokens == NULL || tokens[0] == NULL)
		return (1);
	if (strcmp(tokens[0], "exit") == 0)
		return (0);

	cmd = ky_check_builtins(tokens);
	if (cmd == NULL)
		cmd = ky_find_executable(tokens, argv);
	if (cmd == NULL)
		return (-1);

	return (ky_execute_command(cmd, tokens, argv));
}

/**
 * ky_cnt_tkn - counts the num of tkn
 *@str: str to cnt
 *Return: the num
 */
size_t ky_cnt_tkn(char *str)
{
	size_t n = 0;
	int state = 0;

	while (*str)
	{
		if (*str == ' ' || *str == '\t' || *str == '\n')
			state = 0;
		else if (state == 0)
		{
			state = 1;
			n++;
		}
		str++;

	}
	return (n);
}
/**
 * ky_check_builtins - check if the cmd is a built in
 * @tokens: array
 * Return: name or NULL if not a built-in
 */
char *ky_check_builtins(char **tokens)
{
	(void)tokens;
	return (NULL);
}

/**
 * ky_find_executable - Find the exec
 * @tokens: array
 * @argv: array of arguments
 * Return: the path
 */
char *ky_find_executable(char **tokens, char **argv)
{
	char *cmd, *path, **dirs;
	size_t i;

	cmd = tokens[0];

	if (cmd[0] != '/')
	{
		path = getenv("PATH");
		if (path == NULL)
			return (NULL);
		dirs = ky_input_pasr(path);
		if (dirs == NULL)
			return (NULL);
		for (i = 0; dirs[i] != NULL; i++)
		{
			cmd = malloc(strlen(dirs[i]) +
					strlen(tokens[0]) + 2);
			if (cmd == NULL)
				return (NULL);
			strcpy(cmd, dirs[i]);
			strcat(cmd, "/");
			strcat(cmd, tokens[0]);

			if (access(cmd, X_OK) == 0)
				break;
			free(cmd);
			cmd = NULL;
		}
		free(dirs);

		if (cmd == NULL)
		{
			perror(argv[0]);
			return (NULL);
		}
	}
	return (cmd);
}
