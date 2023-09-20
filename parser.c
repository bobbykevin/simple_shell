#include "shell.h"

/**
 * isExecutableCommand - Determines if a file is an executable command
 * @info: Pointer to the info struct
 * @path: Path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int isExecutableCommand(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * duplicateSubstring - Duplicates characters from a string
 * @pathString: The PATH string
 * @start: Starting index
 * @stop: Stopping index
 *
 * Return: Pointer to a new buffer
 */
char *duplicateSubstring(char *pathString, int start, int stop)
{
	static char buffer[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (pathString[i] != ':')
			buffer[k++] = pathString[i];
	buffer[k] = 0;
	return (buffer);
}

/**
 * findCommandInPath - Finds the specified command in the PATH string
 * @info: Pointer to the info struct
 * @pathString: The PATH string
 * @command: The command to find
 *
 * Return: Full path of the command if found, or NULL
 */
char *findCommandInPath(info_t *info, char *pathString, char *command)
{
	int i = 0, currentPosition = 0;
	char *path;

	if (!pathString)
		return (NULL);
	if ((_strlen(command) > 2) && starts_with(command, "./"))
	{
		if (isExecutableCommand(info, command))
			return (command);
	}
	while (1)
	{
		if (!pathString[i] || pathString[i] == ':')
		{
			path = duplicateSubstring(pathString, currentPosition, i);
			if (!*path)
				_strcat(path, command);
			else
			{
				_strcat(path, "/");
				_strcat(path, command);
			}
			if (isExecutableCommand(info, path))
				return (path);
			if (!pathString[i])
				break;
			currentPosition = i;
		}
		i++;
	}
	return (NULL);
}
