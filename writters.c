#include "shell.h"
/**
 * ky_write - function writes a buffer to a file descriptor
 * @fd: The fd to write
 * @buffer: The buffer
 * @count: no of bytes to write
 * Return: The number of bytes written or -1 if otherwise
 */
ssize_t ky_write(int fd, const void *buffer, size_t count)
{
	ssize_t n;

	if (fd < 0 || buffer == NULL || count == 0)
		return (-1);

	n = write(fd, buffer, count);
	if (n == -1)
	{
		perror("ky_write");
		return (-1);
	}
	return (n);
}

/**
 * sigint_handler - handles the singint
 * @signum: signal num
 */
void sigint_handler(int signum)
{
	(void)signum;
	ky_write(STDOUT_FILENO, "$ ", 2);
}

/**
 * ky_rd_input - Reads the input from STDIN
 * Return: A pointrr to the input
 */
char *ky_rd_input(void)
{
	char *input = NULL;
	size_t len = 0;
	ssize_t n;

	n = getline(&input, &len, stdin);
	if (n == -1)
	{
		if (isatty(STDIN_FILENO))
			ky_write(STDOUT_FILENO, "\n", 1);
		free(input);
		return (NULL);
	}
	input = strtok(input, "\n");
	return (input);
}

/**
 * ky_input_pasr - parse the input
 * @input: The input to parse
 * Return: An array of tkns or Null if No tkn or err
 */
char **ky_input_pasr(char *input)
{
	char **tokens;
	char *token;
	size_t i, n;

	if (input == NULL)
		return (NULL);

	n = ky_cnt_tkn(input);
	if (n == 0)
		return (NULL);

	tokens = malloc(sizeof(char *) * (n + 1));
	if (tokens == NULL)
		return (NULL);

	token = strtok(input, DELIM);
	for (i = 0; i < n; i++)
	{
		tokens[i] = token;
		token = strtok(NULL, DELIM);
	}
	tokens[i] = NULL;

	return (tokens);
}
