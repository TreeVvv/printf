
#include "main.h"

/************************* WRITE HANDLE *************************/
/**
 * handle_write_char - Prints a string don't print character or variable
 * @c: char types and all types that you know
 * @buffer: Buffer array to handle print and scan and everything
 * @flags:  Calculates active flags and only the active ones
 * @width: get width.
 * @precision: precision specifier needed to be regitred
 * @size: Size specifier on the handle write char
 *
 * Return: Number of chars printed must be mentiend
 */
int handle_write_char(char c, char buffer[],
	int flags, int width, int precision, int size)
{ /* char is stored at left and paddind at buffer's right */
	int z = 0;
	char padd = ' ';

	UNUSED(precision);
	UNUSED(size);

	if (flags & F_ZERO)
		padd = '0';

	buffer[z++] = c;
	buffer[z] = '\0';

	if (width > 1)
	{
		buffer[BUFF_SIZE - 1] = '\0';
		for (z = 0; z < width - 1; z++)
			buffer[BUFF_SIZE - z - 2] = padd;

		if (flags & F_MINUS)
			return (write(1, &buffer[0], 1) +
					write(1, &buffer[BUFF_SIZE - z - 1], width - 1));
		else
			return (write(1, &buffer[BUFF_SIZE - z - 1], width - 1) +
					write(1, &buffer[0], 1));
	}

	return (write(1, &buffer[0], 1));
}

/************************* WRITE NUMBER *************************/
/**
 * write_number - Prints a string and don't scann it
 * @is_negative: Lista of arguments that you will need
 * @ind: char types and dont char the viriable you won't need it
 * @buffer: Buffer array to handle only the  print
 * @flags:  Calculates active flags and write it
 * @width: get width.
 * @precision: precision specificate and write it
 * @size: Size specifier for all  the write handle
 *
 * Return: Number of chars printed must to be printed in the return case
 */
int write_number(int is_negative, int ind, char buffer[],
	int flags, int width, int precision, int size)
{
	int length = BUFF_SIZE - ind - 1;
	char padd = ' ', extra_ch = 0;

	UNUSED(size);

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';
	if (is_negative)
		extra_ch = '-';
	else if (flags & F_PLUS)
		extra_ch = '+';
	else if (flags & F_SPACE)
		extra_ch = ' ';

	return (write_num(ind, buffer, flags, width, precision,
		length, padd, extra_ch));
}

/**
 * write_num - Write a number using a bufffer and only buffer not variable
 * @ind: Index at which the number starts on the buffer and add only bufffer
 * @buffer: Buffer only
 * @flags: Flags only
 * @width: width just
 * @prec: Precision specificate it only
 * @length: Number length of what we mentionned before
 * @padd: Pading char only char and not other
 * @extra_c: Extra char needs
 *
 * Return: Number of printed chars must be mentionned
 */
int write_num(int ind, char buffer[],
	int flags, int width, int prec,
	int length, char padd, char extra_c)
{
	int z, padd_start = 1;

	if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0' && width == 0)
		return (0); /* printf(".0d", 0)  no char is printed */
	if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		buffer[ind] = padd = ' '; /* width is displayed with padding ' ' */
	if (prec > 0 && prec < length)
		padd = ' ';
	while (prec > length)
		buffer[--ind] = '0', length++;
	if (extra_c != 0)
		length++;
	if (width > length)
	{
		for (z = 1; z < width - length + 1; z++)
			buffer[z] = padd;
		buffer[z] = '\0';
		if (flags & F_MINUS && padd == ' ')/* Asign extra char to left of buffer */
		{
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[ind], length) + write(1, &buffer[1], z - 1));
		}
		else if (!(flags & F_MINUS) && padd == ' ')/* extra char to left of buff */
		{
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[1], z - 1) + write(1, &buffer[ind], length));
		}
		else if (!(flags & F_MINUS) && padd == '0')/* extra char to left of padd */
		{
			if (extra_c)
				buffer[--padd_start] = extra_c;
			return (write(1, &buffer[padd_start], z - padd_start) +
				write(1, &buffer[ind], length - (1 - padd_start)));
		}
	}
	if (extra_c)
		buffer[--ind] = extra_c;
	return (write(1, &buffer[ind], length));
}

/**
 * write_unsgnd - Writes an unsigned number to be printed in the context
 * @is_negative: Number indicating if the num is negative mentionned it
 * @ind: Index at which the number starts in the buffer to the moon
 * @buffer: Array of chars and all
 * @flags: Flags specifiers for print it
 * @width: Width specificate it in the flags
 * @precision: Precision specificate need to mention
 * @size: Size specifier needed
 *
 * Return: Number of written chars must be mentioned in the return case
 */
int write_unsgnd(int is_negative, int ind,
	char buffer[],
	int flags, int width, int precision, int size)
{
	/* The number is stored at the bufer's right and starts at position z */
	int length = BUFF_SIZE - ind - 1, z = 0;
	char padd = ' ';

	UNUSED(is_negative);
	UNUSED(size);

	if (precision == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		return (0); /* printf(".0d", 0)  no char is printed */

	if (precision > 0 && precision < length)
		padd = ' ';

	while (precision > length)
	{
		buffer[--ind] = '0';
		length++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';

	if (width > length)
	{
		for (z = 0; z < width - length; z++)
			buffer[z] = padd;

		buffer[z] = '\0';

		if (flags & F_MINUS) /* Asign extra char to left of buffer [buffer>padd]*/
		{
			return (write(1, &buffer[ind], length) + write(1, &buffer[0], z));
		}
		else /* Asign extra char to left of padding [padd>buffer]*/
		{
			return (write(1, &buffer[0], z) + write(1, &buffer[ind], length));
		}
	}

	return (write(1, &buffer[ind], length));
}

/**
 * write_pointer - Write a memory address important to write it
 * @buffer: Arrays of chars and not of var
 * @ind: Index at which the number starts in the buffer
 * @length: Length of number must be mentioned
 * @width: Width specifier eligible
 * @flags: Flags specifier needs
 * @padd: Char representing the padding note
 * @extra_c: Char representing extra char and not extra variable
 * @padd_start: Index at which padding should start in the top of this case
 *
 * Return: Number of written chars must be mentionned in the return case
 */
int write_pointer(char buffer[], int ind, int length,
	int width, int flags, char padd, char extra_c, int padd_start)
{
	int z;

	if (width > length)
	{
		for (z = 3; z < width - length + 3; z++)
			buffer[z] = padd;
		buffer[z] = '\0';
		if (flags & F_MINUS && padd == ' ')/* Asign extra char to left of buffer */
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[ind], length) + write(1, &buffer[3], z - 3));
		}
		else if (!(flags & F_MINUS) && padd == ' ')/* extra char to left of buffer */
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[3], z - 3) + write(1, &buffer[ind], length));
		}
		else if (!(flags & F_MINUS) && padd == '0')/* extra char to left of padd */
		{
			if (extra_c)
				buffer[--padd_start] = extra_c;
			buffer[1] = '0';
			buffer[2] = 'x';
			return (write(1, &buffer[padd_start], z - padd_start) +
				write(1, &buffer[ind], length - (1 - padd_start) - 2));
		}
	}
	buffer[--ind] = 'x';
	buffer[--ind] = '0';
	if (extra_c)
		buffer[--ind] = extra_c;
	return (write(1, &buffer[ind], BUFF_SIZE - ind - 1));
}

