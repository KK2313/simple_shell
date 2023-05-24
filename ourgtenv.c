#include "ourshel.h"

/**
 * get_environ - returns the string array copy of our environ
 * @inf: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **get_environ(info_t *inf)
{
	if (!inf->environ || inf->env_changed)
	{
		inf->environ = list_to_strings(inf->env);
		inf->env_changed = 0;
	}

	return (inf->environ);
}

/**
 * _unsetenv - Remove an environment variable
 * @inf: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @var: the string env var property
 */
int _unsetenv(info_t *inf, char *var)
{
	list_t *apex= inf->env;
	size_t j = 0;
	char *w;

	if (!apex || !var)
		return (0);

	while (apex)
	{
		w = starts_with(apex->str, var);
		if (w && *w == '=')
		{
			inf->env_changed = delete_apex_at_index(&(inf->env), i);
			j = 0;
			apex = inf->env;
			continue;
		}
		apex = apex->next;
		j++;
	}
	return (inf->env_changed);
}

/**
 * _setenv - Initialize a new environment variable,
 *             or modify an existing one
 * @inf: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string env var property
 * @value: the string env var value
 *  Return: Always 0
 */
int _setenv(info_t *inf, char *var, char *value)
{
	char *cbuf = NULL;
	list_t *apex;
	char *w;

	if (!var || !value)
		return (0);

	cbuf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!cbuf)
		return (1);
	_strcpy(cbuf, var);
	_strcat(cbuf, "=");
	_strcat(cbuf, value);
	apex = inf->env;
	while (apex)
	{
		w = starts_with(apex->str, var);
		if (w && *w == '=')
		{
			free(apex->str);
			apex->str = cbuf;
			inf->env_changed = 1;
			return (0);
		}
		apex = apex->next;
	}
	add_apex_end(&(inf->env), cbuf, 0);
	free(cbuf);
	inf->env_changed = 1;
	return (0);
}
