#include "ourshell.h"

/**
 * retrieve_environ_var - ..
 * @env_var: var
 * @data: program's data
 * Return: ..
 */
char *retrieve_environ_var(char *env_var, data_of_program *data)
{
	int i, key_length = 0;

	if (env_var == NULL || data->env == NULL)
		return (NULL);
	key_length = string_length(env_var);

	for (i = 0; data->env[i]; i++)
	{
		if (string_compare(env_var, data->env[i], key_length) &&
		 data->env[i][key_length] == '=')
		{
			return (data->env[i] + key_length + 1);
		}
	}
	return (NULL);
}

/**
 * environ_set_key - overide current key
 * @key: var
 * @value: new value
 * @data: program's data
 * Return: 0, 1 or 2
 */

int environ_set_key(char *key, char *value, data_of_program *data)
{
	int i, key_length = 0, is_new_key = 1;

	if (key == NULL || value == NULL || data->env == NULL)
		return (1);

	key_length = string_length(key);

	for (i = 0; data->env[i]; i++)
	{
		if (string_compare(key, data->env[i], key_length) &&
		 data->env[i][key_length] == '=')
		{
			is_new_key = 0;
			free(data->env[i]);
			break;
		}
	}
	data->env[i] = string_join(str_dup(key), "=");
	data->env[i] = string_join(data->env[i], value);

	if (is_new_key)
	{
		data->env[i + 1] = NULL;
	}
	return (0);
}

/**
 * environ_delete_key - get rid of a key
 * @key: test par
 * @data: program's data
 * Return: 1 or 0
 */
int environ_delete_key(char *key, data_of_program *data)
{
	int i, key_length = 0;

	if (key == NULL || data->env == NULL)
		return (0);

	key_length = string_length(key);

	for (i = 0; data->env[i]; i++)
	{
		if (string_compare(key, data->env[i], key_length) &&
		 data->env[i][key_length] == '=')
		{
			free(data->env[i]);

			i++;
			for (; data->env[i]; i++)
			{
				data->env[i - 1] = data->env[i];
			}
			data->env[i - 1] = NULL;
			return (1);
		}
	}
	return (0);
}


/**
 * display_environ - rep current env
 * @data: program's data
 */
void display_environ(data_of_program *data)
{
	int j;

	for (j = 0; data->env[j]; j++)
	{
		our_print(data->env[j]);
		our_print("\n");
	}
}

