#include "ourshel.h"

/**
 * _strcpy - copies a string
 * @pst: the destination
 * @orgn: the source
 *
 * Return: pointer to destination
 */
char *_strcpy(char *pst, char *orgn)
{
	int j = 0;

	if (pst == orgn || orgn == 0)
		return (pst);
	while (orgn[j])
	{
		pst[j] = orgn[j];
		j++;
	}
	pst[j] = 0;
	return (pst);
}

/**
 * _strdup - duplicates a string
 * @string: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *_strdup(const char *string)
{
	int lgth = 0;
	char *wr;

	if (string == NULL)
		return (NULL);
	while (*string++)
		lgth++;
	wr = malloc(sizeof(char) * (lgth + 1));
	if (!wr)
		return (NULL);
	for (lgth++; lgth--;)
		wr[lgth] = *--string;
	return (wr);
}

/**
 * _puts - prints an input string
 * @string: the string to be printed
 *
 * Return: Nothing
 */
void _puts(char *string)
{
	int j = 0;

	if (!string)
		return;
	while (string[j] != '\0')
	{
		_putchar(string[i]);
		j++;
	}
}

/**
 * _putchar - writes the character g to stdout
 * @g: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char g)
{
	static int j;
	static char buf[WRITE_BUF_SIZE];

	if (g == BUF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(1, buf, j);
		j = 0;
	}
	if (g != BUF_FLUSH)
		buf[j++] = c;
	return (1);
}
