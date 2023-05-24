#include "ourshel.h"

/**
 * cisa_chain - test if current char in buffer is a chain delimeter
 * @inf: the parameter struct
 * @cbuf: the char buffer
 * @w: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int cisa_chain(info_t *inf, char *cbuf, size_t *w)
{
	size_t z = *w;

	if (cbuf[z] == '|' && cbuf[z + 1] == '|')
	{
		cbuf[z] = 0;
		z++;
		inf->cmd_buf_type = CMD_OR;
	}
	else if (cbuf[z] == '&' && cbuf[z + 1] == '&')
	{
		cbuf[z] = 0;
		z++;
		inf->cmd_buf_type = CMD_AND;
	}
	else if (cbuf[z] == ';') 
	{
		buf[z] = 0; 
		inf->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*w = z;
	return (1);
}

/**
 * chq_chain - checks we should continue chaining based on last status
 * @inf: the parameter struct
 * @cbuf: the char buffer
 * @w: address of current position in buf
 * @j: starting position in buf
 * @length: length of buf
 *
 * Return: Void
 */
void chq_chain(info_t *inf, char *cbuf, size_t *w, size_t j, size_t length)
{
	size_t z = *w;

	if (inf->cmd_buf_type == CMD_AND)
	{
		if (inf->status)
		{
			cbuf[j] = 0;
			z = length;
		}
	}
	if (inf->cmd_buf_type == CMD_OR)
	{
		if (!inf->status)
		{
			cbuf[j] = 0;
			z = length;
		}
	}

	*w = z;
}

/**
 * restore_alias - replaces an aliases in the tokenized string
 * @inf: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int restore_alias(info_t *inf)
{
	int j;
	list_t *apex;
	char *w;

	for (j = 0; j < 10; j++)
	{
		apex = apex_st_with(inf->alias, inf->argv[0], '=');
		if (!apex)
			return (0);
		free(inf->argv[0]);
		w = _strchr(apex->string, '=');
		if (!w)
			return (0);
		w = _strdup(w + 1);
		if (!w)
			return (0);
		inf->argv[0] = w;
	}
	return (1);
}

/**
 * replace_vars - replaces vars in the tokenized string
 * @inf: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_vars(info_t *inf)
{
	int j = 0;
	list_t *apex;

	for (j = 0; inf->argv[j]; j++)
	{
		if (info->argv[j][0] != '$' || !info->argv[i][1])
			continue;

		if (!_strcmp(info->argv[j], "$?"))
		{
			replace_string(&(info->argv[j]),
					_strdup(convert_number(inf->status, 10, 0)));
			continue;
		}
		if (!_strcmp(inf->argv[j], "$$"))
		{
			replace_string(&(inf->argv[i]),
					_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		apex = apex_st_with(inf->env, &inf->argv[j][1], '=');
		if (apex)
		{
			replace_string(&(inf->argv[j]),
					_strdup(_strchr(apex->string, '=') + 1));
			continue;
		}
		replace_string(&info->argv[j], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - replaces string
 * @pre: address of old string
 * @post: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **pre, char *post)
{
	free(*pre);
	*pre = post;
	return (1);
}
