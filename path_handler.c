#include "ourshell.h"

/**
 * identify_program - ..
 * @data: the program's data
 * Return: 0
 */
int identify_program(data_of_program *data)
{
	int i = 0, path = 0;
	char **directories;

	if (!data->command_name)
		return (2);

	if (data->command_name[0] == '/' || data->command_name[0] == '.')
		return (scan_file(data->command_name));

	free(data->toks[0]);
	data->toks[0] = str_join(str_dup("/"), data->command_name);
	if (!data->toks[0])
		return (2);

	directories = divide_path(data);

	if (!directories || !directories[0])
	{
		errno = 127;
		return (127);
	}
	for (i = 0; directories[i]; i++)
	{
		directories[i] = str_join(directories[i], data->toks[0]);
		path = scan_file(directories[i]);
		if (path == 0 || path  == 126)
		{
			errno = 0;
			free(data->toks[0]);
			data->toks[0] = str_dup(directories[i]);
			free_pointers_array(directories);
			return (path);
		}
	}
	free(data->toks[0]);
	data->toks[0] = NULL;
	free_pointers_array(directories);
	return (path);
}

/**
 * divide_path - divide the path into directories
 * @data: program's data
 * Return: directories
 */
char **divide_path(data_of_program *data)
{
	int i = 0;
	char *PATH;
	int c_directories = 2;
	char **tokens = NULL;

	PATH = get_env_var("PATH", data);
	if ((PATH == NULL) || PATH[0] == '\0')
	{
		return (NULL);
	}

	PATH = str_dup(PATH);

	for (i = 0; PATH[i]; i++)
	{
		if (PATH[i] == ':')
			c_directories++;
	}

	toks = malloc(sizeof(char *) * c_directories);

	i = 0;
	toks[i] = str_dup(_strtok(PATH, ":"));
	while (toks[i++])
	{
		toks[i] = str_dup(_strtok(NULL, ":"));
	}

	free(PATH);
	PATH = NULL;
	return (toks);

}

/**
 * scan_file - check file
 * @entire_path: file path
 * Return: 0
 */
int scan_file(char *entire_path)
{
	struct stat sb;

	if (stat(entire_path, &sb) != -1)
	{
		if (S_ISDIR(sb.st_mode) ||  access(entire_path, X_OK))
		{
			errno = 126;
			return (126);
		}
		return (0);
	}
	errno = 127;
	return (127);
}

