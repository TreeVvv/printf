#include "main.h"
/**
 * handle_print - Prints an argument based on its type and not its weight
 * @fmt: Formatted string which needs to be printed the arguments and marque it well.
 * @list: List of arguments to be printed in the file.
 * @ind: ind.ind
 * @buffer: Buffer array to handle print and buffer it.
 * @flags: Calculates active flags using variables
 * @width: get width and not type
 * @precision: Precision specificate the handle print
 * @size: Size specifier needs 
 * Return: 1 or 2; mentionned
 */
int handle_print(const char *fmt, int *ind, va_list list, char buffer[],
	int flags, int width, int precision, int size)
{
	int j, unknow_len = 0, printed_chars = -1;
	fmt_t fmt_types[] = {
		{'c', print_char}, {'s', print_string}, {'%', print_percent},
		{'i', print_int}, {'d', print_int}, {'b', print_binary},
		{'u', print_unsigned}, {'o', print_octal}, {'x', print_hexadecimal},
		{'X', print_hexa_upper}, {'p', print_pointer}, {'S', print_non_printable},
		{'r', print_reverse}, {'R', print_rot13string}, {'\0', NULL}
	};
	for (j = 0; fmt_types[j].fmt != '\0'; j++)
		if (fmt[*ind] == fmt_types[j].fmt)
			return (fmt_types[j].fn(list, buffer, flags, width, precision, size));

	if (fmt_types[j].fmt == '\0')
	{
		if (fmt[*ind] == '\0')
			return (-1);
		unknow_len += write(1, "%%", 1);
		if (fmt[*ind - 1] == ' ')
			unknow_len += write(1, " ", 1);
		else if (width)
		{
			--(*ind);
			while (fmt[*ind] != ' ' && fmt[*ind] != '%')
				--(*ind);
			if (fmt[*ind] == ' ')
				--(*ind);
			return (1);
		}
		unknow_len += write(1, &fmt[*ind], 1);
		return (unknow_len);
	}
	return (printed_chars);
}

