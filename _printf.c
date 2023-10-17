#include "main.h"

void print_buffer(char buffer[], int *buff_ind);

/**
 * _printf - Printf function is the code i am working on.
 * @format: format fonction is needed in codes below.
 * Return: Printed chars is using for character.
 */
int _printf(const char *format, ...)
{
	int h, printed = 0, printed_chars = 0;
	int flags, width, precision, size, buff_ind = 0;
	va_list list;
	char buffer[BUFF_SIZE];

	if (format == NULL)
		return (-1);

	va_start(list, format);

	for (h = 0; format && format[h] != '\0'; h++)
	{
		if (format[h] != '%')
		{
			buffer[buff_ind++] = format[h];
			if (buff_ind == BUFF_SIZE)
				print_buffer(buffer, &buff_ind);
			/* write(1, &format[h], 1);*/
			printed_chars++;
		}
		else
		{
			print_buffer(buffer, &buff_ind);
			flags = get_flags(format, &h);
			width = get_width(format, &h, list);
			precision = get_precision(format, &h, list);
			size = get_size(format, &h);
			++h;
			printed = handle_print(format, &h, list, buffer,
				flags, width, precision, size);
			if (printed == -1)
				return (-1);
			printed_chars += printed;
		}
	}

	print_buffer(buffer, &buff_ind);

	va_end(list);

	return (printed_chars);
}

/**
 * print_buffer - Prints the buff content
 * @buffer: Array of chars and buffer
 * @buff_ind: Index at where to edit or add next char, represents the large.
 */
void print_buffer(char buffer[], int *buff_ind)
{
	if (*buff_ind > 0)
		write(1, &buffer[0], *buff_ind);

	*buff_ind = 0;
}
