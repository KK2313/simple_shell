#include "ourshel.h"

/**
 * _strlen - returns the length of a string
 * @n: the string whose length to check
 *
 * Return: integer length of string
 */
int _strlen(char *n)
{
	int j = 0;

	if (!n)
		return (0);

	while (*n++)
		j++;
	return (j);
}

/**
 * _strcmp - performs lexicogarphic comparison of two strangs.
 * @n1: the first string
 * @n2: the second string
 *
 * Return: negative if n1 < n2, positive if n1 > n2, zero if n1 == n2
 */
int _strcmp(char *n1, char *n2)
{
	while (*n1 && *n2)
	{
		if (*n1 != *n2)
			return (*n1 - *n2);
		n1++;
		n2++;
	}
	if (*n1 == *n2)
		return (0);
	else
		return (*n1 < *n2 ? -1 : 1);
}

/**
 * st_with - checks if needle starts with jaystck
 * @jaystck: string to search
 * @jiggle: the substring to find
 *
 * Return: address of next char of jaystck or NULL
 */
char *st_with(const char *jaystck, const char *jiggle)
{
	while (*jiggle)
		if (*jiggle++ != *jaystck++)
			return (NULL);
	return ((char *)jaystck);
}

/**
 * _strcat - concatenates two strings
 * @pst: the destination buffer
 * @orgn: the source buffer
 *
 * Return: pointer to destination buffer
 */
char *_strcat(char *pst, char *orgn)
{
	char *wr = pst;

	while (*pst)
		pst++;
	while (*orgn)
		*pst++ = *orgn++;
	*pst = *orgn;
	return (wr);
}
