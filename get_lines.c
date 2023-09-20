#include "shell.h"

/**
 * bufferInput - Buffers chained commands.
 * @info: Parameter struct.
 * @buf: Address of the buffer.
 * @len: Address of the length variable.
 *
 * Return: Bytes read.
 */
ssize_t bufferInput(info_t *info, char **buf, size_t *len)
{
	ssize_t bytesRead = 0;
	size_t len_p = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);

		bytesRead = _getline(info, buf, &len_p);

		if (bytesRead > 0)
		{
			if ((*buf)[bytesRead - 1] == '\n')
			{
				(*buf)[bytesRead - 1] = '\0';
				bytesRead--;
			}

			info->linecount_flag = 1;
			removeComments(*buf);
			buildHistoryList(info, *buf, info->histcount++);

			{
				*len = bytesRead;
				info->cmd_buf = buf;
			}
		}
	}

	return (bytesRead);
}

/**
 * getInput - Gets a line without the newline character.
 * @info: Parameter struct.
 *
 * Return: Bytes read.
 */
ssize_t getInput(info_t *info)
{
	static char *buf;
	static size_t i, j, len;
	ssize_t bytesRead = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	bytesRead = bufferInput(info, &buf, &len);

	if (bytesRead == -1)
		return (-1);

	if (len)
	{
		j = i;
		p = buf + i;

		checkCommandChain(info, buf, &j, i, len);

		while (j < len)
		{
			if (isCommandChain(info, buf, &j))
				break;
			j++;
		}

		i = j + 1;

		if (i >= len)
		{
			i = len = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p;
		return (_strlen(p));
	}

	*buf_p = buf;
	return (bytesRead);
}

/**
 * readBuffer - Reads a buffer.
 * @info: Parameter struct.
 * @buf: Buffer.
 * @i: Size.
 *
 * Return: Bytes read.
 */
ssize_t readBuffer(info_t *info, char *buf, size_t *i)
{
	ssize_t bytesRead = 0;

	if (*i)
		return (0);

	bytesRead = read(info->readfd, buf, READ_BUF_SIZE);

	if (bytesRead >= 0)
		*i = bytesRead;

	return (bytesRead);
}

/**
 * _custom_getline - Gets the next line of input from STDIN.
 * @info: Parameter struct.
 * @ptr: Address of the pointer to the buffer, preallocated or NULL.
 * @length: Size of the preallocated ptr buffer if not NULL.
 *
 * Return: Number of bytes read.
 */
int _custom_getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t bytesRead = 0, totalBytesRead = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		totalBytesRead = *length;

	if (i == len)
		i = len = 0;

	bytesRead = readBuffer(info, buf, &len);

	if (bytesRead == -1 || (bytesRead == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, totalBytesRead, p ? totalBytesRead + k : k + 1);

	if (!new_p)
		return (p ? (free(p), -1) : -1);

	if (p)
		_strncat(new_p, buf + i, k - i);
	else
		_custom_strncpy(new_p, buf + i, k - i + 1);

	totalBytesRead += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = totalBytesRead;

	*ptr = p;
	return (totalBytesRead);
}

/**
 * sigintHandler - Blocks Ctrl-C.
 * @sig_num: The signal number.
 *
 * Return: Void.
 */
void sigintHandler(__attribute__((unused)) int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
