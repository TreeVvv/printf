#include "main.h"

/********* PRINT CHAR *********/

/**
 * print_char - Prints a char for printing character 
 * @types: List a of all arguments that we have to print with
 * @buffer: Add buffer array to handle print as thinking for
 * @flags: For calculating active flags
 * @width: Width and edit
 * @precision: specificat precision
 * @size: Specifier
 * Return: Number of return chars printed
 */
int print_char(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char c = va_arg(types, int);

	return (handle_write_char(c, buffer, flags, width, precision, size));
}
/********* PRINT A STRING *********/
/**
 * print_string - String to print on.
 * @types: Add arguments as a list
 * @buffer: Buffer array to handle print
 * @flags:  Calculates numbers of active flags.
 * @width: get width and edit .
 * @precision: Specificat precisions
 * @size: specifier
 * Return: Number of return chars printed
 */
int print_string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int length = 0, y;
	char *str = va_arg(types, char *);

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	if (str == NULL)
	{
		str = "(null)";
		if (precision >= 6)
			str = "      ";
	}

	while (str[length] != '\0')
		length++;

	if (precision >= 0 && precision < length)
		length = precision;

	if (width > length)
	{
		if (flags & F_MINUS)
		{
			write(1, &str[0], length);
			for (y = width - length; y > 0; y--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (y = width - length; y > 0; y--)
				write(1, " ", 1);
			write(1, &str[0], length);
			return (width);
		}
	}

	return (write(1, str, length));
}
/********* PRINT PERCENT SIGN *********/
/**
 * print_percent - Percent sign need to be printed
 * @types: Give a list of arguments
 * @buffer:  handle print - Buffer
 * @flags:  Calculates active flags
 * @width: width get it and edit it.
 * @precision: Precision specification
 * @size: specification
 * Return: all number of chars need to be printed .
 */
int print_percent(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	UNUSED(types);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	return (write(1, "%%", 1));
}

/********* PRINT INT *********/
/**
 * print_int - Print int
 * @types: arguments list needs for knowing the type
 * @buffer: Buffer array need it to handle prnt
 * @flags:  Calculates the number of active flags
 * @width: getting width and editing it.
 * @precision: specificat precision.
 * @size: Specifier the size of the print int 
 * Return: Number of return chars not printed
 */
int print_int(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int y = BUFF_SIZE - 2;
	int is_negative = 0;
	long int n = va_arg(types, long int);
	unsigned long int num;

	n = convert_size_number(n, size);

	if (n == 0)
		buffer[y--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';
	num = (unsigned long int)n;

	if (n < 0)
	{
		num = (unsigned long int)((-1) * n);
		is_negative = 1;
	}

	while (num > 0)
	{
		buffer[y--] = (num % 10) + '0';
		num /= 10;
	}

	y++;

	return (write_number(is_negative, y, buffer, flags, width, precision, size));
}

/********* PRINT BINARY *********/
/**
 * print_binary - Prints a binary  number which is ignsired
 * @types: all List of arguments
 * @buffer: array to handle print need buffer 
 * @flags:  active flags to be calculated
 * @width: width to get and edit.
 * @precision: Specificat precision
 * @size: specificate the size of the print binary
 * Return: Numbers of return char printed.
 */
int print_binary(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	unsigned int n, m, y, sum;
	unsigned int a[32];
	int count;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	n = va_arg(types, unsigned int);
	m = 2147483648; /* (2 ^ 31) */
	a[0] = n / m;
	for (y = 1; y < 32; y++)
	{
		m /= 2;
		a[y] = (n / m) % 2;
	}
	for (y = 0, sum = 0, count = 0; y < 32; y++)
	{
		sum += a[y];
		if (sum || y == 31)
		{
			char z = '0' + a[y];

			write(1, &z, 1);
			count++;
		}
	}
	return (count);
}
