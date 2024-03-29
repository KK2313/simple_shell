#include "ourshell.h"
/**
 * _strtok - split str
 * @line: command
 * @delimator: marker
 * Return: result
*/
char *_strtok(char *line, char *delimator)
{
	int j;
	static char *str;
	char *copystr;

	if (line != NULL)
		str = line;
	for (; *str != '\0'; str++)
	{
		for (j = 0; delimator[j] != '\0'; j++)
		{
			if (*str == delimator[j])
			break;
		}
		if (delimator[j] == '\0')
			break;
	}
	copystr = str;
	if (*copystr == '\0')
		return (NULL);
	for (; *str != '\0'; str++)
	{
		for (j = 0; delimator[j] != '\0'; j++)
		{
			if (*str == delimator[j])
			{
				*str = '\0';
				str++;
				return (copystr);
			}
		}
	}
	return (copystr);
}

/**
 * split_str - ..
 * @data: the program's data
 * Return: different commands
 */
void split_str(data_of_program *data)
{
	char *delimiter = " \t";
	int i, j, counter = 2, length;

	length = str_len(data->input_line);
	if (length)
	{
		if (data->input_line[length - 1] == '\n')
			data->input_line[length - 1] = '\0';
	}

	for (i = 0; data->input_line[i]; i++)
	{
		for (j = 0; delimiter[j]; j++)
		{
			if (data->input_line[i] == delimiter[j])
				counter++;
		}
	}

	data->tokens = malloc(counter * sizeof(char *));
	if (data->tokens == NULL)
	{
		perror(data->program_name);
		exit(errno);
	}
	i = 0;
	data->tokens[i] = str_dup(_strtok(data->input_line, delimiter));
	data->command_name = str_dup(data->tokens[0]);
	while (data->tokens[i++])
	{
		data->tokens[i] = str_dup(_strtok(NULL, delimiter));
	}
}

