#include "ourshell.h"

/**
 * str_len - find len of str
 * @str: test par
 * Return: len
 */
int str_len(char *str)
{
	int length = 0;

	if (str == NULL)
		return (0);

	while (str[length++] != '\0')
	{
	}
	return (--length);
}
