#include "shell.h"
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
		return (ky_print_env());
	}
	if (params[0][0] == '/')
	{
		return (ky_execute_full_path(params));
	}
	else
	{
		return (ky_execute_in_path(params));
	}
}

/**
 * ky_print_env - print all environment variables
 *
 * Return: 1 on success, 0 on failure
 */
int ky_print_env(void)
{
	char **env = environ;

	while (*env != NULL)
	{
		printf("%s\n", *env);
		env++;
	}
	return (1);
}

/**
 * ky_execute_full_path - execute a command from a full path
 * @params: parameters for the command
 *
 * Return: 1 on success, 0 on failure
 */
int ky_execute_full_path(char **params)
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

/**
 * ky_execute_in_path - execute a command in the PATH
 * @params: parameters for the command
 *
 * Return: 1 on success, 0 on failure
 */
int ky_execute_in_path(char **params)
{
	char *path = getenv("PATH");
	char *path_copy = strdup(path);
	char *dir = strtok(path_copy, ":");

	while (dir != NULL)
	{
		int result = ky_handle_command(dir, params);

		if (result != -1)
		{
			free(path_copy);
			return (result);
		}
		dir = strtok(NULL, ":");
	}
	printf("shell: %s: command not found\n", params[0]);
	free(path_copy);
	return (0);
}
