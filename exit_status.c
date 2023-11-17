#include "shell.h"

/**
 * hndl_exit - function handles exit status
 * @command: status of input to handle
 * Return: void
 */
void hndl_exit(char **command)
{
	if (command[1] != NULL)
	{
		int status = handle_exit_status(command[1]);

		exit(status);
	}
}

/**
 * handle_exit_status - function handles the exit status
 * @status_str: string representation of the status
 * Return: integer representation of the status
 */
int handle_exit_status(char *status_str)
{
	char *endptr;
	long status = strtol(status_str, &endptr, 10);

	if (*endptr != '\0')
	{
		printf("Invalid integer argument for exit status\n");
		exit(EXIT_FAILURE);
	}

	return ((int)status);
}

