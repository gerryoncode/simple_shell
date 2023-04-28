#include "main.h"

/**
 * long_to_string - converts a number to a string.
 * @number: number to be converten in an string.
 * @string: buffer to save the number as string.
 * @base: base to convert number
 *
 * Return: Nothing.
 */
void long_to_str(long num, char *str, int base)
{
	int ind = 0, inNeg = 0;
	long coin = num;
	char letters[] = {"0123456789abcdef"};

	if (coin == 0)
		str[ind++] = '0';

	if (str[0] == '-')
		inNeg = 1;

	while (coin)
	{
		if (coin < 0)
			str[ind++] = letters[-(coin % base)];
		else
			str[ind++] = letters[coin % base];
		coin /= base;
	}
	if (inNeg)
		str[ind] = '-';

	str[ind] = '\0';
	str_reverse(str);
}


/**
 * _atoi - string to integer.
 *
 * @s: pointer to str.
 * Return: int of string or 0.
 */
int _atoi(char *s)
{
	int sign = 1;
	unsigned int num = 0;
	
	while (!('0' <= *s && *s <= '9') && *s != '\0')
	{
		if (*s == '-')
			sign *= -1;
		if (*s == '+')
			sign *= +1;
		s++;
	}

	
	while ('0' <= *s && *s <= '9' && *s != '\0')
	{

		num = (num * 10) + (*s - '0');
		s++;
	}
	return (num * sign);
}

/**
 * count_char - count the coincidences of char in str.
 *
 * @str: pointer to str.
 * @chara: string with  chars to count
 * Return: int of string or 0.
 */
int count_char(char *str, char *chara)
{
	int i = 0, count = 0;

	for (; str[i]; i++)
	{
		if (str[i] == chara[0])
			count++;
	}
	return (count);
}
