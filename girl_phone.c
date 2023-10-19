#include "main.h"

/**
 * get_precision - Calculates the precision for printing and not  for scanning
 * @format: Formatted string in which to print the arguments for doing it well
 * @i: List of arguments to be printedon the first list 
 * @list: list of arguments for the get precision
 *
 * Return: Precision note must be announced 
 */
int get_precision(const char *format, int *i, va_list list)
{
	int curr_j = *i + 1;
	int precision = -1;

	if (format[curr_j] != '.')
		return (precision);

	precision = 0;

	for (curr_j += 1; format[curr_j] != '\0'; curr_j++)
	{
		if (is_digit(format[curr_j]))
		{
			precision *= 10;
			precision += format[curr_j] - '0';
		}
		else if (format[curr_j] == '*')
		{
			curr_j++;
			precision = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*i = curr_j - 1;

	return (precision);
}

