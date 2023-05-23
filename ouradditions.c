#include "ourshell.h"

/**
 * exp_variables - ..
 * @data: pointer to the program's data
 */
void exp_variables(data_of_program *data)
{
	int i, j;
	char line[BUFFER_SIZE] = {0}, expansion[BUFFER_SIZE] = {'\0'}, *temp;

	if (data->input_line == NULL)
		return;
	add_string(line, data->input_line);
	for (i = 0; line[i]; i++)
		if (line[i] == '#')
			line[i--] = '\0';
		else if (line[i] == '$' && line[i + 1] == '?')
		{
			line[i] = '\0';
			number_to_string(errno, expansion, 10);
			add_string(line, expansion);
			add_string(line, data->input_line + i + 2);
		}
		else if (line[i] == '$' && line[i + 1] == '$')
		{
			line[i] = '\0';
			number_to_string(getpid(), expansion, 10);
			add_string(line, expansion);
			add_string(line, data->input_line + i + 2);
		}
		else if (line[i] == '$' && (line[i + 1] == ' ' || line[i + 1] == '\0'))
			continue;
		else if (line[i] == '$')
		{
			for (j = 1; line[i + j] && line[i + j] != ' '; j++)
				expansion[j - 1] = line[i + j];
			temp = get_env_var(expansion, data);
			line[i] = '\0', expansion[0] = '\0';
			add_string(expansion, line + i + j);
			temp ? add_string(line, temp) : 1;
			add_string(line, expansion);
		}
	if (!string_compare(data->input_line, line, 0))
	{
		free(data->input_line);
		data->input_line = string_duplicate(line);
	}
}

/**
 * more_alias - ..
 * @data: program's data
 */
void other_aliases(data_of_program *data)
{
	int i, j, was_expanded = 0;
	char line[BUFFER_SIZE] = {0}, expansion[BUFFER_SIZE] = {'\0'}, *temp;

	if (data->input_line == NULL)
		return;

	add_string(line, data->input_line);

	for (i = 0; line[i]; i++)
	{
		for (j = 0; line[i + j] && line[i + j] != ' '; j++)
			expansion[j] = line[i + j];
		expansion[j] = '\0';

		temp = retrieve_alias(data, expansion);
		if (temp)
		{
			expansion[0] = '\0';
			add_string(expansion, line + i + j);
			line[i] = '\0';
			add_string(line, temp);
			line[str_len(line)] = '\0';
			add_string(line, expansion);
			was_expanded = 1;
		}
		break;
	}
	if (was_expanded)
	{
		free(data->input_line);
		data->input_line = string_duplicate(line);
	}
}

/**
 * add_string - append string at end of the buffer
 * @buffer: buffer
 * @str: value
 * Return: 0
 */
int add_string(char *buffer, char *str)
{
	int length, i;

	length = string_length(buffer);
	for (i = 0; str[i]; i++)
	{
		buffer[length + i] = str[i];
	}
	buffer[length + i] = '\0';
	return (length + i);
}

