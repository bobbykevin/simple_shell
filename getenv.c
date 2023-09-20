#include "shell.h"

/**
 * getEnvironmentStrings - Returns a copy of the environment as a string array.
 * @info: Pointer to the info_t structure.
 *
 * Return: A string array containing the environment variables.
 */
char **getEnvironmentStrings(info_t *info)
{
	if (!info->environ || info->envChanged)
	{
		info->environ = convertEnvListToStringArray(info->env);
		info->envChanged = 0;
	}

	return (info->environ);
}

/**
 * unsetEnvironmentVariable - Removes an environment variable.
 * @info: Pointer to the info_t structure.
 * @variable: The name of the environment variable to remove.
 *
 * Return: 1 if the variable is deleted, 0 otherwise.
 */
int unsetEnvironmentVariable(info_t *info, char *variable)
{
	list_t *node = info->env;
	size_t index = 0;
	char *p;

	if (!node || !variable)
		return (0);

	while (node)
	{
		p = startsWith(node->str, variable);
		if (p && *p == '=')
		{
			info->envChanged = deleteNodeAtIndex(&(info->env), index);
			index = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		index++;
	}
	return (info->envChanged);
}

/**
 * setEnvironmentVariable - Initializes a new envi var or modifies an existing.
 * @info: Pointer to the info_t structure.
 * @variable: The name of the environment variable.
 * @value: The value to set for the environment variable.
 *
 * Return: Always 0.
 */
int setEnvironmentVariable(info_t *info, char *variable, char *value)
{
	char *envString = NULL;
	list_t *node;
	char *p;

	if (!variable || !value)
		return (0);

	envString = malloc(_strlen(variable) + _strlen(value) + 2);
	if (!envString)
		return (1);
	_strcpy(envString, variable);
	_strcat(envString, "=");
	_strcat(envString, value);
	node = info->env;
	while (node)
	{
		p = startsWith(node->str, variable);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = envString;
			info->envChanged = 1;
			return (0);
		}
		node = node->next;
	}
	addNodeEnd(&(info->env), envString, 0);
	free(envString);
	info->envChanged = 1;
	return (0);
}
