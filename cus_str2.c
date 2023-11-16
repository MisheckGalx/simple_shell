#include "shell.h"

/**
<<<<<<< HEAD
=======
 * ky_getliine - Read a line from the standard input
 * @lineptr: Pointer to the buffer
 * @n: Number of characters to read
 * @stream: The input stream to red from
 *
 * Return: The number of characters read, or -1 on failure
 */
ssize_t ky_getline(char **lineptr, size_t *n, FILE *stream)
{
	char *buffer;
	ssize_t characters;

	buffer = malloc(1024);
	if (buffer == NULL)
	{
		return (-1);
	}

	characters = read(fileno(stream), buffer, 1024);
	if (characters == -1)
	{
		free(buffer);
		return (-1);
	}

	buffer[characters] = '\0';
	*lineptr = buffer;
	*n = characters;

	return (characters);
}

/**
>>>>>>> e6f513bc28fe3f72458100d67bacc5713fa2382d
 * ky_strlen - Compute length of string
 * @s: The string to be sized
 *
 * Return: The length of the string
 */
size_t ky_strlen(const char *s)
{
	const char *p = s;

	while (*p)
		++p;
	return (p - s);
}

/**
 * ky_strtok - Braek string str into a series of tokens
 * @str: The string to be separated
 * @delim: The delimiter character
 *
 * Return: Pointer to the next token , or NULL
 */
char *ky_strtok(char *str, const char *delim)
{
	static char *src;
	char *p, *ret = 0;

	if (str != NULL)
		src = str;

	if (src == NULL)
		return (NULL);

	p = strpbrk(src, delim);

	if (p != NULL)
	{
		*p = 0;
		ret = src;
		src = ++p;
	}
	else if (*src)
	{
		ret = src;
		src = NULL;
	}

	return (ret);
}
/**
 * ky_strdup - Duplicate a string
 * @s: The string to be duplicated
 *
 * Return: Pointer to the duplicated string
 */
char *ky_strdup(const char *s)
{
	size_t len = ky_strlen(s) + 1;
	void *new = malloc(len);

	if (new == NULL)
		return (NULL);

	return ((char *) memcpy(new, s, len));
}
