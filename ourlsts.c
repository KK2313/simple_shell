#include "ourshel.h"

/**
 * add_apex - adds a node to the start of the list
 * @lead: address of pointer to head node
 * @string: str field of node
 * @no: node index used by history
 *
 * Return: size of list
 */
list_t *add_apex(list_t **lead, const char *string, int no)
{
	list_t *new_lead;

	if (!lead)
		return (NULL);
	new_lead = malloc(sizeof(list_t));
	if (!new_lead)
		return (NULL);
	_memf((void *)new_lead, 0, sizeof(list_t));
	new_head->no = no;
	if (string)
	{
		new_lead->string = _strdup(string);
		if (!new_lead->string)
		{
			free(new_lead);
			return (NULL);
		}
	}
	new_lead->next = *lead;
	*lead = new_lead;
	return (new_lead);
}

/**
 * add_apex_end - adds a node to the end of the list
 * @lead: address of pointer to head node
 * @string: str field of node
 * @no: node index used by history
 *
 * Return: size of list
 */
list_t *add_apex_end(list_t **lead, const char *string, int no)
{
	list_t *new_apex, *apex;

	if (!lead)
		return (NULL);

	apex = *lead;
	new_apex = malloc(sizeof(list_t));
	if (!new_apex)
		return (NULL);
	_memf((void *)new_apex, 0, sizeof(list_t));
	new_apex->no = no;
	if (string)
	{
		new_apex->string = _strdup(string);
		if (!new_apex->string)
		{
			free(new_apex);
			return (NULL);
		}
	}
	if (apex)
	{
		while (apex->next)
			apex = apex->next;
		apex->next = new_apex;
	}
	else
		*lead = new_apex;
	return (new_apex);
}

/**
 * dsp_list_str - prints only the str element of a list_t linked list
 * @p: pointer to first node
 *
 * Return: size of list
 */
size_t dsp_list_str(const list_t *p)
{
	size_t j = 0;

	while (p)
	{
		_puts(p->str ? p->str : "(nil)");
		_puts("\n");
		p = p->next;
		j++;
	}
	return (j);
}

/**
 * del_apex_at_index - deletes node at given index
 * @lead: address of pointer to first node
 * @indx: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int del_apex_at_index(list_t **lead, unsigned int indx)
{
	list_t *apex, *prev_apex;
	unsigned int j = 0;

	if (!lead || !*lead)
		return (0);

	if (!indx)
	{
		apex = *lead;
		*lead = (*lead)->next;
		free(apex->str);
		free(apex);
		return (1);
	}
	apex = *lead;
	while (apex)
	{
		if (j == indx)
		{
			prev_apex->next = apex->next;
			free(apex->str);
			free(apex);
			return (1);
		}
		j++;
		prev_apex = apex;
		apex = apex->next;
	}
	return (0);
}

/**
 * free_ls - frees all nodes of a list
 * @lead_pointer: address of pointer to head node
 *
 * Return: void
 */
void free_ls(list_t **lead_pointer)
{
	list_t *apex, *next_apex, *lead;

	if (!lead_pointer || !*lead_pointer)
		return;
	lead = *lead_pointer;
	apex = lead;
	while (apex)
	{
		next_apex = apex->next;
		free(apex->str);
		free(apex);
		apex = next_apex;
	}
	*lead_pointer = NULL;
}
