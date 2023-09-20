#include "shell.h"

/**
 * customMemset - Fills memory with a constant byte
 * @memory: Pointer to the memory area
 * @byte: The byte to fill the memory area with
 * @size: The number of bytes to be filled
 *
 * Return: A pointer to the memory area
 */
char *customMemset(char *memory, char byte, unsigned int size)
{
	unsigned int i;

	for (i = 0; i < size; i++)
		memory[i] = byte;
	return (memory);
}

/**
 * freeStringArray - Frees an array of strings
 * @stringArray: Array of strings to be freed
 */
void freeStringArray(char **stringArray)
{
	char **temp = stringArray;

	if (!stringArray)
		return;
	while (*stringArray)
		free(*stringArray++);
	free(temp);
}

/**
 * customRealloc - Reallocates a block of memory
 * @previousBlock: Pointer to the previously allocated block
 * @oldSize: Byte size of the previous block
 * @newSize: Byte size of the new block
 *
 * Return: Pointer to the reallocated block
 */
void *customRealloc(void *previousBlock, unsigned int oldSize, unsigned int newSize)
{
	char *newBlock;

	if (!previousBlock)
		return (malloc(newSize));
	if (!newSize)
		return (free(previousBlock), NULL);
	if (newSize == oldSize)
		return (previousBlock);

	newBlock = malloc(newSize);
	if (!newBlock)
		return (NULL);

	oldSize = oldSize < newSize ? oldSize : newSize;
	while (oldSize--)
		newBlock[oldSize] = ((char *)previousBlock)[oldSize];
	free(previousBlock);
	return (newBlock);
}
