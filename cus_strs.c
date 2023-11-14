#include "shell.h"

/**
 * ky_strcpy - Copy the string pointed by source to destination
 * @dest: The destination where the content isd to be copied
 * @src: This is the string to be copied
 *
 * Return: This returns the destination string
 */
char *ky_strcpy(char *dest, const char *src)
{
	char *start = dest;

	while (*src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
	}

	*dest = '\0';
	return (start);
}

/**
 * ky_strcat - Concatenate the string pointed by source to destination
 * @dest: The destination where the content is to be appended
 * @src: This is the string to be concatenated
 *
 * Return: This returns the destination string
 */
char *ky_strcat(char *dest, const char *src)
{
	char *start = dest;

	while (*dest)
	{
		dest++;
	}

	while (*src)
	{
		*dest = *src;
		dest++;
		src++;
	}

	*dest = '\0';
	return (start);
}


/**
 * ky_strcmp - compare two strings
 * @s1: The first string to be compared
 * @s2: The second string to be compared
 *
 * Return: If s1 < s2, it returns a negative number.If s1 > s2, it returns
 * a positive number. If s1 == s2, it returns 0.
 */
int ky_strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}

	return (*(const unsigned char *)s1 - *(const unsigned char *)s2);
}


/**
 * ky_strcspn - Calculate the length of the initial segment of str1 which
 * consists entirely of characters not in str2
 * @str1: The string to be scanned
 * @str2: The characters to be searched for
 *
 * Return: This returns the number of characters in the initial segment of
 * str1 which are not in str2
 */
size_t ky_strcspn(const char *str1, const char *str2)
{
	const char *ptr;
	const char *s1;

	for (s1 = str1; *s1 != '\0'; s1++)
	{
		for (ptr = str2; *ptr != '\0'; ptr++)
		{
			if (*s1 == *ptr)
			{
				return (s1 - str1);
			}
		}
	}

	return (s1 - str1);
}
