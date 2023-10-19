#include "main.h"

/**
 * is_printable - Evaluates if a char is printable and not scanned 
 * @c: Char to be evaluated all the characters
 *
 * Return: 1 if c is printable, 0 otherwise and be mentionned all what it change
 */
int is_printable(char c)
{
	if (c >= 32 && c < 127)
		return (1);

	return (0);
}

/**
 * append_hexa_code - Append ascci in hexadecimal code and  buffer the hexadecimal code
 * @buffer: Array of chars and not the characters
 * @i: Index at which to start appending all of the project
 * @ascii_code: ASSCI CODE to be mentionned for the hexacode
 * Return: Always 3 and must be mentionned
 */
int append_hexa_code(char ascii_code, char buffer[], int a)
{
	char map_to[] = "0123456789ABCDEF";
	/* The hexa format code is always 2 digits long */
	if (ascii_code < 0)
		ascii_code *= -1;

	buffer[a++] = '\\';
	buffer[a++] = 'x';

	buffer[a++] = map_to[ascii_code / 16];
	buffer[a] = map_to[ascii_code % 16];

	return (3);
}

/**
 * is_digit - Verifies if a char is a digit and not a variable
 * @c: Char to be evaluated all the characteres
 *
 * Return: 1 if c is a digit, 0 otherwise must be mentionned in all returns
 */
int is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);

	return (0);
}

/**
 * convert_size_number - Casts a size number to be casted and covert it
 * @num: Number to be casted and not printed
 * @size: Number indicating the type to be casted on the tipe
 *
 * Return: Casted value of num and mention it
 */
long int convert_size_number(long int num, int size)
{
	if (size == S_LONG)
		return (num);
	else if (size == S_SHORT)
		return ((short)num);

	return ((int)num);
}

/**
 * convert_size_unsgnd - Casts a number specified size
 * @num: Number to be casted for printed on
 * @size: Number indicating type to casted
 *
 * Return: Casted value of num must be mentined
 */
long int convert_size_unsgnd(unsigned long int num, int size)
{
	if (size == S_LONG)
		return (num);
	else if (size == S_SHORT)
		return ((unsigned short)num);

	return ((unsigned int)num);
}

