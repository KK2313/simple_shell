#include "ourshell.h"

/**
 * show_alias - function to display aliases
 * @data: program's data
 * @alias: alias's name to be printed
 * Return: 0
 */
int show_alias(data_of_program *data, char *alias)
{
	int i, j, alias_length;
	char buffer[250] = {'\0'};

	if (data->alias_list)
	{
		alias_length = string_length(alias);
		for (i = 0; data->alias_list[i]; i++)
		{
			if (!alias || (string_compare(data->alias_list[i], alias, alias_length)
				&&	data->alias_list[i][alias_length] == '='))
			{
				for (j = 0; data->alias_list[i][j]; j++)
				{
					buffer[j] = data->alias_list[i][j];
					if (data->alias_list[i][j] == '=')
						break;
				}
				buffer[j + 1] = '\0';
				add_string(buffer, "'");
				add_string(buffer, data->alias_list[i] + j + 1);
				add_string(buffer, "'\n");
				our_print(buffer);
			}
		}
	}

	return (0);
}

/**
 * alias_retreval - retreive aliases
 * @data: struct for the program's data
 * @name: name of the requested alias.
 * Return: 0
 */
char *alias_retreval(data_of_program *data, char *name)
{
	int i, alias_length;

	if (name == NULL || data->alias_list == NULL)
		return (NULL);

	alias_length = string_length(name);

	for (i = 0; data->alias_list[i]; i++)
	{
		if (string_compare(name, data->alias_list[i], alias_length) &&
			data->alias_list[i][alias_length] == '=')
		{
			return (data->alias_list[i] + alias_length + 1);
		}
	}
	return (NULL);

}

/**
 * override_alias - implement alias
 * @alias_string: value
 * @data: program's data structure
 * Return: 0
 */
int override_alias(char *alias_string, data_of_program *data)
{
	int i, j;
	char buffer[250] = {'0'}, *temp = NULL;

	if (alias_string == NULL ||  data->alias_list == NULL)
		return (1);
	for (i = 0; alias_string[i]; i++)
		if (alias_string[i] != '=')
			buffer[i] = alias_string[i];
		else
		{
			temp = alias_retreval(data, alias_string + i + 1);
			break;
		}

	for (j = 0; data->alias_list[j]; j++)
		if (string_compare(buffer, data->alias_list[j], i) &&
			data->alias_list[j][i] == '=')
		{
			free(data->alias_list[j]);
			break;
		}

	if (temp)
	{
		add_string(buffer, "=");
		add_string(buffer, temp);
		data->alias_list[j] = string_duplicate(buffer);
	}
	else
		data->alias_list[j] = string_duplicate(alias_string);
	return (0);
}

