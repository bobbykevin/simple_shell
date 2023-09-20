#include "shell.h"

/**
 * freeAndNull - Frees a pointer and sets it to NULL
 * @ptr: Address of the pointer to free
 *
 * Return: 1 if freed, otherwise 0.
 */
int freeAndNull(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
