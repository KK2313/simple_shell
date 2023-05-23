#include "ourshell.h"

/**
 * display_env - show env
 * @data: struct for the program's data
 * Return: 0
 */
int show_env(data_of_program *data)
{
	int i;
	char cpname[50] = {'\0'};
	char *var_copy = NULL;

	if (data->tokens[1] == NULL)
		display_environ(data);
	else
	{
		for (i = 0; data->tokens[1][i]; i++)
		{
			if (data->tokens[1][i] == '=')
			{
				var_copy = string_duplicate(get_env_var(cpname, data));
				if (var_copy != NULL)
					environ_set_key(cpname, data->tokens[1] + i + 1, data);

				display_environ(data);
				if (retrieve_env_var(cpname, data) == NULL)
				{
					our_print(data->tokens[1]);
					our_print("\n");
				}
				else
				{
					environ_set_key(cpname, var_copy, data);
					free(var_copy);
				}
				return (0);
			}
			cpname[i] = data->tokens[1][i];
		}
		errno = 2;
		perror(data->command_name);
		errno = 127;
	}
	return (0);
}

/**
 * build_env - set up env
 * @data: program's data
 * Return: 0
 */
int build_env(data_of_program *data)
{
	if (data->tokens[1] == NULL || data->tokens[2] == NULL)
		return (0);
	if (data->tokens[3] != NULL)
	{
		errno = E2BIG;
		perror(data->command_name);
		return (5);
	}

	environ_set_key(data->tokens[1], data->tokens[2], data);

	return (0);
}

/**
 * delete_env - unbuild env
 * @data: program's data'
 * Return: 0
 */
int delete_env(data_of_program *data)
{
	if (data->tokens[1] == NULL)
		return (0);
	if (data->tokens[2] != NULL)
	{
		errno = E2BIG;
		perror(data->command_name);
		return (5);
	}
	env_delete_key(data->tokens[1], data);

	return (0);
}

/**
 * ourbuiltin1 - our builtin functions that run matches
 * @data: struct for the program's data
 * Return: executed function or -1
 */
int ourbuiltin1(data_of_program *data)
{
	int iterator;
	builtins options[] = {
		{"exit", ourexit},
		{"help", ourhelp},
		{"cd", ourcd},
		{"alias", another_alias},
		{"env", show_env},
		{"setenv", buid_env},
		{"unsetenv", delete_env},
		{NULL, NULL}
	};

	for (iterator = 0; options[iterator].builtin != NULL; iterator++)
	{
		if (string_compare(options[iterator].builtin, data->command_name, 0))
		{
			return (options[iterator].function(data));
		}
	}
	return (-1);
}

