#include "shell.h"

/**
 * _custom_strncpy - Copies a string up to n characters.
 * @dest: The destination string to be copied to.
 * @src: The source string.
 * @n: The maximum number of characters to copy.
 *
 * Return: The modified destination string.
 */
char *_custom_strncpy(char *dest, const char *src, size_t n)
{
	char *original_dest = dest;

	while (*src != '\0' && n > 0)
	{
		*dest++ = *src++;
		n--;
	}

	while (n > 0)
	{
		*dest++ = '\0';
		n--;
	}

	return (original_dest);
}

/**
 * _custom_strncat - Concatenates two strings up to n characters.
 * @dest: The destination string.
 * @src: The source string to append.
 * @n: The maximum number of characters to append.
 *
 * Return: The modified destination string.
 */
char *_custom_strncat(char *dest, const char *src, size_t n)
{
	char *original_dest = dest;

	while (*dest != '\0')
		dest++;

	while (*src != '\0' && n > 0)
	{
		*dest++ = *src++;
		n--;
	}

	*dest = '\0';

	return (original_dest);
}

/**
 * _custom_strchr - Locates the first occurrence of a character in a string.
 * @s: The string to be searched.
 * @c: The character to look for.
 *
 * Return: pointer to the first occurrence of the char in the string or NULL if not found.
 */
char *_custom_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == c)
			return ((char *)s);
		s++;
	}

	return (NULL);
}
