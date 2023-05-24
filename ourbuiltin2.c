#include "ourshell.h"

/**
 * exit_builtin - function to close prog
 * @data: struct for the program's data
 * Return: 0 or error
 */
int exit_builtin(data_of_program *data)
{
	int i;

	if (data->tokens[1] != NULL)
	{
		for (i = 0; data->tokens[1][i]; i++)
			if ((data->tokens[1][i] < '0' || data->tokens[1][i] > '9')
				&& data->tokens[1][i] != '+')
			{
				errno = 2;
				return (2);
			}
		errno = string_to_integer(data->tokens[1]);
	}
	free_data(data);
	exit(errno);
}

/**
 * cd_builtin - change dir
 * @data: struct for the program's data
 * Return: 0 or error
 */
int cd_builtin(data_of_program *data)
{
	char *dir_home = retrieve_env_var("HOME", data), *dir_old = NULL;
	char old_dir[128] = {0};
	int error_code = 0;

	if (data->tokens[1])
	{
		if (string_compare(data->tokens[1], "-", 0))
		{
			dir_old = retrieve_env_var("OLDPWD", data);
			if (dir_old)
				error_code = mk_directory(data, dir_old);
			our_print(retrieve_env_var("PWD", data));
			our_print("\n");

			return (error_code);
		}
		else
		{
			return (mk_directory(data, data->tokens[1]));
		}
	}
	else
	{
		if (!dir_home)
			dir_home = getcwd(old_dir, 128);

		return (mk_directory(data, dir_home));
	}
	return (0);
}

/**
 * mk_directory - create dir
 * @data: struct for the program's data
 * @new_dir: implementation
 * Return: 0 or error
 */
int mk_directory(data_of_program *data, char *new_dir)
{
	char old_dir[128] = {0};
	int err_code = 0;

	getcwd(old_dir, 128);

	if (!string_compare(old_dir, new_dir, 0))
	{
		err_code = chdir(new_dir);
		if (err_code == -1)
		{
			errno = 2;
			return (3);
		}
		environ_set_key("PWD", new_dir, data);
	}
	environ_set_key("OLDPWD", old_dir, data);
	return (0);
}

/**
 * help_builtin - display env
 * @data: struct for the program's data
 * Return: 0 or error
 */
int help_builtin(data_of_program *data)
{
	int i, length = 0;
	char *mensajes[6] = {NULL};

	mensajes[0] = HELP_MSG;

	if (data->tokens[1] == NULL)
	{
		our_print(mensajes[0] + 6);
		return (1);
	}
	if (data->tokens[2] != NULL)
	{
		errno = E2BIG;
		perror(data->command_name);
		return (5);
	}
	mensajes[1] = HELP_EXIT_MSG;
	mensajes[2] = HELP_ENV_MSG;
	mensajes[3] = HELP_SETENV_MSG;
	mensajes[4] = HELP_UNSETENV_MSG;
	mensajes[5] = HELP_CD_MSG;

	for (i = 0; mensajes[i]; i++)
	{
		length = string_length(data->tokens[1]);
		if (string_compare(data->tokens[1], mensajes[i], length))
		{
			our_print(mensajes[i] + length + 1);
			return (1);
		}
	}
	errno = EINVAL;
	perror(data->command_name);
	return (0);
}

/**
 * remaining_aliases - handle remaining aliases
 * @data: struct for the program's data
 * Return: 0
 */
int remaining_aliases(data_of_program *data)
{
	int i = 0;

	if (data->tokens[1] == NULL)
		return (show_alias(data, NULL));

	while (data->tokens[++i])
	{
		if (character_count(data->tokens[i], "="))
			override_alias(data->tokens[i], data);
		else
			show_alias(data, data->tokens[i]);
	}

	return (0);
}

