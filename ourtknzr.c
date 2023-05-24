#include "ourshel.h"

/**
 * **stw - splits a string into words. Repeat delimiters are ignored
 * @string: the input string
 * @h: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **stw(char *string, char *h)
{
	int j, z, r, l, nowords = 0;
	char **x;

	if (string == NULL || string[0] == 0)
		return (NULL);
	if (!h)
		h = " ";
	for (j = 0; string[j] != '\0'; j++)
		if (!is_delim(string[j], h) && (is_delim(string[j + 1], h) || !string[j + 1]))
			nowords++;

	if (nowords == 0)
		return (NULL);
	x = malloc((1 + nowords) * sizeof(char *));
	if (!x)
		return (NULL);
	for (j = 0, z = 0; z < nowords; z++)
	{
		while (is_delim(string[j], h))
			j++;
		r = 0;
		while (!is_delim(string[j + r], h) && string[j + r])
			r++;
		x[z] = malloc((r + 1) * sizeof(char));
		if (!x[z])
		{
			for (r = 0; r < z; r++)
				free(x[r]);
			free(x);
			return (NULL);
		}
		for (l = 0; l < r; l++)
			x[z][l] = string[j++];
		x[z][l] = 0;
	}
	x[z] = NULL;
	return (x);
}

/**
 * **stwi - splits a string into words
 * @string: the input string
 * @h: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **stwi(char *string, char h)
{
	int j, z, r, l, nowords = 0;
	char **x;

	if (string == NULL || string[0] == 0)
		return (NULL);
	for (j = 0; string[j] != '\0'; j++)
		if ((string[j] != h && string[j + 1] == h) ||
				    (string[j] != h && !string[j + 1]) || string[j + 1] == d)
			nowords++;
	if (nowords == 0)
		return (NULL);
	x = malloc((1 + nowords) * sizeof(char *));
	if (!x)
		return (NULL);
	for (j = 0, z = 0; z < nowords; z++)
	{
		while (string[j] == h && string[j] != h)
			j++;
		r = 0;
		while (string[j + r] != h && string[j + r] && string[j + r] != h)
			r++;
		x[z] = malloc((r + 1) * sizeof(char));
		if (!x[z])
		{
			for (r = 0; r < z; r++)
				free(x[r]);
			free(x);
			return (NULL);
		}
		for (l = 0; l < r; l++)
			x[z][l] = string[j++];
		x[z][l] = 0;
	}
	x[z] = NULL;
	return (x);
}
