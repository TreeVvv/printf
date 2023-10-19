#include "main.h"

/****************** PRINT POINTER ******************/
/**
 * print_pointer - Print number of pointer variable
 * @types: List all  arguments you need on
 * @buffer: Buffer array to handle prints 
 * @flags:  Calculates only the active flags
 * @width: get width and not character
 * @precision: Precision specificate for printing number
 * @size: Size specifier for kkep the ram 
 * Return: Number of chars printed to be mentionned for all of that
 */
int print_pointer(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char extra_c = 0, padd = ' ';
	int ing = BUFF_SIZE - 2, length = 2, padd_start = 1; /* length=2, for '0x' */
	unsigned long num_addrs;
	char map_to[] = "0123456789abcdef";
	void *addrs = va_arg(types, void *);

	UNUSED(width);
	UNUSED(size);

	if (addrs == NULL)
		return (write(1, "(nil)", 5));

	buffer[BUFF_SIZE - 1] = '\0';
	UNUSED(precision);

	num_addrs = (unsigned long)addrs;

	while (num_addrs > 0)
	{
		buffer[ing--] = map_to[num_addrs % 16];
		num_addrs /= 16;
		length++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';
	if (flags & F_PLUS)
		extra_c = '+', length++;
	else if (flags & F_SPACE)
		extra_c = ' ', length++;

	ing++;

	/*return (write(1, &buffer[i], BUFF_SIZE - i - 1));*/
	return (write_pointer(buffer, ing, length,
		width, flags, padd, extra_c, padd_start));
}

/************************* PRINT NON PRINTABLE *************************/
/**
 * print_non_printable - Prints ascii coddzfdes in hexa of non printable chars and not character
 * @types: Lista of arguments that we will need 
 * @buffer: Buffer array to handle print and go on to keep it 
 * @flags:  Calculates active flags for printing non printibale
 * @width: get widthfor for the coddzfdales
 * @precision: Precision specificate for make it clear
 * @size: Size specifier the print non printable
 * Return: Number of chars printed it must be mentionned
 */
int print_non_printable(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int r = 0, offset = 0;
	char *str = va_arg(types, char *);

	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		return (write(1, "(null)", 6));

	while (str[r] != '\0')
	{
		if (is_printable(str[r]))
			buffer[r + offset] = str[r];
		else
			offset += append_hexa_code(str[r], buffer, r + offset);

		r++;
	}

	buffer[r + offset] = '\0';

	return (write(1, buffer, r + offset));
}

/************************* PRINT REVERSE *************************/
/**
 * print_reverse - Prints reverse string and not variable.
 * @types: Lista of arguments of print reverse
 * @buffer: Buffer array to handle print reverse
 * @flags:  Calculates active flags only flags and not others
 * @width: get width all that
 * @precision: Precision specificate all this
 * @size: Size specifier which is importing 
 * Return: Numbers of chars printed
 */

int print_reverse(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char *str;
	int r, count = 0;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(size);

	str = va_arg(types, char *);

	if (str == NULL)
	{
		UNUSED(precision);

		str = ")Null(";
	}
	for (r = 0; str[r]; r++)
		;

	for (r = r - 1; r >= 0; r--)
	{
		char z = str[r];

		write(1, &z, 1);
		count++;
	}
	return (count);
}
/************************* PRINT A STRING IN ROT13 *************************/
/**
 * print_rot13string - Print a string in rot13string .
 * @types: Lista of arguments what you need 
 * @buffer: Buffer array to handle print for moving it
 * @flags:  Calculates only active flags
 * @width: get width and arrays
 * @precision: Precision specificate for doing best
 * @size: Size specifier for calculate ram
 * Return: Numbers of chars printed must be mentionned
 */
int print_rot13string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char x;
	char *str;
	unsigned int r, j;
	int count = 0;
	char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	str = va_arg(types, char *);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		str = "(AHYY)";
	for (r = 0; str[r]; r++)
	{
		for (j = 0; in[j]; j++)
		{
			if (in[j] == str[r])
			{
				x = out[j];
				write(1, &x, 1);
				count++;
				break;
			}
		}
		if (!in[j])
		{
			x = str[r];
			write(1, &x, 1);
			count++;
		}
	}
	return (count);
}

