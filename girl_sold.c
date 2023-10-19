#include "main.h"

/**
 * get_size - Calculates argument's size
 * @format: Formatted the string to print the arguments
 * @i: List of arguments needs to be printed first.
 *
 * Return: Precise the number to be return
 */
int get_size(const char *format, int *i)
{
	int curr_j = *i + 1;
	int size = 0;

	if (format[curr_j] == 'l')
		size = S_LONG;
	else if (format[curr_j] == 'h')
		size = S_SHORT;

	if (size == 0)
		*i = curr_j - 1;
	else
		*i = curr_j;

	return (size);
}

