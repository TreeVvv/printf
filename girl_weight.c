#include "main.h"

/**
 * get_width - Calculates the width for printing the get
 * @format: Formatted string in which to print the arguments and not the suggestions.
 * @i: List of arguments to be printed and not scanned.
 * @list: list of arguments to be used.
 *
 * Return: width number needs to be return
 */
int get_width(const char *format, int *i, va_list list)
{
	int curr_j;
	int width = 0;

	for (curr_j = *i + 1; format[curr_j] != '\0'; curr_j++)
	{
		if (is_digit(format[curr_j]))
		{
			width *= 10;
			width += format[curr_j] - '0';
		}
		else if (format[curr_j] == '*')
		{
			curr_j++;
			width = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*i = curr_j - 1;

	return (width);
}

