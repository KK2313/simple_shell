#include "ourshel.h"

/**
 * ls_length - determines length of linked list
 * @w: pointer to first node
 *
 * Return: size of list
 */
size_t ls_length(const list_t *p)
{
	size_t j = 0;

	while (p)
	{
		p = p->next;
		j++;
	}
	return (j);
}

/**
 * ls_to_str - returns an array of strings of the list->str
 * @lead: pointer to first apex
 *
 * Return: array of strings
 */
char **ls_to_str(list_t *lead)
{
	list_t *apex = lead;
	size_t j = ls_length(lead), z;
	char **strings;
	char *string;

	if (!lead || !j)
		return (NULL);
	strings = malloc(sizeof(char *) * (j + 1));
	if (!strings)
		return (NULL);
	for (j = 0; apex; apex = apex->next, j++)
	{
		string = malloc(_strlen(apex->string) + 1);
		if (!string)
		{
			for (z = 0; z < j; z++)
				free(strings[z]);
			free(strings);
			return (NULL);
		}

		string = _strcpy(string, apex->string);
		strings[j] = string;
	}
	strings[j] = NULL;
	return (strings);
}


/**
 * dsp_list - prints all elements of a list_t linked list
 * @p: pointer to first apex
 *
 * Return: size of list
 */
size_t dsp_list(const list_t *p)
{
	size_t j = 0;

	while (p)
	{
		_puts(convert_number(p->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(p->str ? p->str : "(nil)");
		_puts("\n");
		p = p->next;
		j++;
	}
	return (j);
}

/**
 * apex_st_with - returns apex whose string starts with prefix
 * @apex: pointer to list head
 * @cyfix: string to match
 * @g: the next character after cyfix to match
 *
 * Return: match apex or null
 */
list_t *apex_st_with(list_t *apex, char *cyfix, char g)
{
	char *w = NULL;

	while (apex)
	{
		w = starts_with(apex->str, cyfix);
		if (w && ((g == -1) || (*w == g)))
			return (apex);
		apex = apex->next;
	}
	return (NULL);
}

/**
 * get_apex_index - gets the index of a apex
 * @lead: pointer to list head
 * @apex: pointer to the apex
 *
 * Return: index of apex or -1
 */
ssize_t get_apex_index(list_t *lead, list_t *apex)
{
	size_t j = 0;

	while (lead)
	{
		if (lead == apex)
			return (i);
		lead = lead->next;
		j++;
	}
	return (-1);
}
