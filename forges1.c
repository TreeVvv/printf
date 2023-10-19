#include "main.h"

/************************* PRINT UNSIGNED NUMBER *************************/
/**
 * print_unsigned - Prints an unsigned number and  not alphabet
 * @types: List a of arguments related to the number
 * @buffer: Buffer array to handle print and not character
 * @flags:  Calculates all active flags
 * @width: get all width that you know 
 * @precision: pecify  Precisions
 * @size: Size specifier
 * Return: Number of chars printed and not scanned.
 */
int print_unsigned(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int S = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[S--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[S--] = (num % 10) + '0';
		num /= 10;
	}

	S++;

	return (write_unsgnd(0, S, buffer, flags, width, precision, size));
}

/************* PRINT UNSIGNED NUMBER IN OCTAL  ****************/
/**
 * print_octal - Prints an unsigned number in octal planet
 * @types: Lista of arguments word
 * @buffer: Buffer array to handle just the print variable
 * @flags:  Calculates active flags if you like if you don't like don't calculate it 
 * @width: get allwidth you need
 * @precision: Precision specificate all it 
 * @size: Size specifier the number
 * Return: Number of chars printed must be writed in the return phase
 */
int print_octal(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{

	int s = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[s--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[s--] = (num % 8) + '0';
		num /= 8;
	}

	if (flags & F_HASH && init_num != 0)
		buffer[s--] = '0';

	s++;

	return (write_unsgnd(0, s, buffer, flags, width, precision, size));
}

/************** PRINT UNSIGNED NUMBER IN HEXADECIMAL **************/
/**
 * print_hexadecimal - Prints hexadecimal needed
 * @types: Lista of arguments about the hexadecimal
 * @buffer: Buffer array to handle print which is hexadecimal
 * @flags:  Calculates all active flags that you know 
 * @width: get all width you need for that
 * @precision: Precision specificate
 * @size: Size specifier for printing hexadecimal
 * Return: Number of chars printed must be mentionned
 */
int print_hexadecimal(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789abcdef", buffer,
		flags, 'x', width, precision, size));
}

/************* PRINT UNSIGNED NUMBER IN UPPER HEXADECIMAL **************/
/**
 * print_hexa_upper - Prints an number upper_hexadecimal
 * @types: Lista of arguments for hexa_upper number
 * @buffer: Buffer array to handle print which is hexa_upper number
 * @flags:  Calculates all active flags that you know
 * @width: get all width you need for that
 * @precision: Precision specificate
 * @size: Size specifier for printing all that
 * Return: Number of chars printed must be writed 
 */
int print_hexa_upper(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789ABCDEF", buffer,
		flags, 'X', width, precision, size));
}

/************** PRINT HEXX NUM IN LOWER OR UPPER **************/
/**
 * print_hexa - Prints a hexadecimal number in lower or/and upper
 * @types: Lista of arguments that you need for this project
 * @map_to: Array of values to map the number to hexidecimale
 * @buffer: Buffer array to handle printn all of the file
 * @flags:  Calculates active flags olny not more
 * @flag_ch: Calculates active flags only not more
 * @width: get all width you need for that
 * @precision: Precision specificate
 * @size: Size specifier for printing the hexa
 * @size: Size specifier for printing all that
 * Return: Number of chars printed must be writed
 */
int print_hexa(va_list types, char map_to[], char buffer[],
	int flags, char flag_ch, int width, int precision, int size)
{
	int s = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[s--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[s--] = map_to[num % 16];
		num /= 16;
	}

	if (flags & F_HASH && init_num != 0)
	{
		buffer[s--] = flag_ch;
		buffer[s--] = '0';
	}

	s++;

	return (write_unsgnd(0, s, buffer, flags, width, precision, size));
}

