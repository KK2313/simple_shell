#include "ourshel.h"

/**
 **_strncpy - copies a string
 *@pst: the destination string to be copied to
 *@orgn: the source string
 *@m: the amount of characters to be copied
 *Return: the concatenated string
 */
char *_strncpy(char *pst, char *orgn, int m)
{
	int j, z;
	char *x = pst;

	j = 0;
	while (orgn[j] != '\0' && j < n - 1)
	{
		pst[j] = orgn[j];
		j++;
	}
	if (j < m)
	{
		z = j;
		while (z < m)
		{
			pst[z] = '\0';
			z++;
		}
	}
	return (x);
}

/**
 **_strncat - concatenates two strings
 *@pst: the first string
 *@orgn: the second string
 *@m: the amount of bytes to be maximally used
 *Return: the concatenated string
 */
char *_strncat(char *pst, char *orgn, int m)
{
	int j, z;
	char *x = pst;

	j = 0;
	z = 0;
	while (pst[j] != '\0')
		j++;
	while (orgn[z] != '\0' && z < m)
	{
		pst[j] = orgn[z];
		j++;
		z++;
	}
	if (z < m)
		pst[j] = '\0';
	return (x);
}

/**
 **_strchr - locates a character in a string
 *@x: the string to be parsed
 *@g: the character to look for
 *Return: (x) a pointer to the memory area x
 */
char *_strchr(char *x, char g)
{
	do {
		if (*x == g)
			return (x);
	} while (*x++ != '\0');

	return (NULL);
}
