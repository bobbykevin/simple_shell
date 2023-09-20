#include "shell.h"

/**
 * initializeInfo - Initializes the info_t struct.
 * @info: Pointer to the info_t structure to be initialized.
 */
void initializeInfo(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * populateInfo - Populates the info_t struct with arguments.
 * @info: Pointer to the info_t structure to be populated.
 * @argv: Argument vector.
 */
void populateInfo(info_t *info, char **argv)
{
	int i = 0;

	info->fname = argv[0];
	if (info->arg)
	{
		info->argv = splitString(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = duplicateString(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		replaceAliases(info);
		replaceVariables(info);
	}
}

/**
 * freeInfo - Frees the fields of the info_t struct.
 * @info: Pointer to the info_t structure.
 * @freeAll: true if freeing all fields.
 */
void freeInfo(info_t *info, int freeAll)
{
	freeStringArray(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (freeAll)
	{
		if (!info->cmd_buf)
			free(info->arg);
		freeList(&(info->env));
		freeList(&(info->history));
		freeList(&(info->alias));
		freeStringArray(info->environ);
		info->environ = NULL;
		freeBufferArray((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		flushBuffer();
	}
}
