#include "shell.h"

/**
 * _custom_erratoi - Converts a string to an integer.
 * @s: The string to be converted.
 *
 * Return: The converted number if successful, -1 on error.
 */
int _custom_erratoi(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;

	for (i = 0; s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		els
			return (-1);
	}

	return (result);
}

/**
 * _custom_print_error - Prints an error message.
 * @info: Pointer to the info_t structure.
 * @error_msg: String containing the specified error message.
 */
void _custom_print_error(info_t *info, char *error_msg)
{
	_custom_eputs(info->fname);
	_custom_eputs(": ");
	_custom_print_d(info->line_count, STDERR_FILENO);
	_custom_eputs(": ");
	_custom_eputs(info->argv[0]);
	_custom_eputs(": ");
	_custom_eputs(error_msg);
}

/**
 * _custom_print_d - Prints a decimal (integer) number (base 10).
 * @input: The input number to print.
 * @fd: The file descriptor to write to.
 *
 * Return: The number of characters printed.
 */
int _custom_print_d(int input, int fd)
{
	int (*custom_putchar)(char) = (fd == STDERR_FILENO) ? _custom_eputchar : _custom_putchar;
	int i, count = 0;
	unsigned int abs_num, current;

	abs_num = (input < 0) ? -input : input;

	if (input < 0)
	{
		custom_putchar('-');
		count++;
	}

	current = abs_num;

	for (i = 1000000000; i > 1; i /= 10)
	{
		if (abs_num / i)
		{
			custom_putchar('0' + current / i);
			count++;
		}
		current %= i;
	}

	custom_putchar('0' + current);
	count++;

	return (count);
}

/**
 * _custom_convert_number - Converts a number to a string.
 * @num: The number to convert.
 * @base: The base for conversion.
 * @flags: Argument flags.
 *
 * Return: The converted string.
 */
char *_custom_convert_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';
	}

	array = (flags & CONVERT_LOWERCASE) ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * _custom_remove_comments - Replaces the first instance of '#' with '\0'.
 * @buf: Address of the string to modify.
 */
void _custom_remove_comments(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
	{
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
	}
}
