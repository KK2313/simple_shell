#include "ourshell.h"

/**
 * our_print - function to output chars
 * @str: test par
 * Return: count int
 */
int our_print(char *str)
{
	return (write(STDOUT_FILENO, str, str_len(str)));
}
/**
 * our_printe - Prints character arrays in stderr
 * @str: test par
 * Return: count output
 */
intour _printe(char *str)
{
	return (write(STDERR_FILENO, str, str_len(str)));
}

/**
 *our _print_error - ..
 * @data: program's data'
 * @errorcode: error code
 * Return: count ouput
 */
int our_print_error(int errorcode, data_of_program *data)
{
	char n_as_string[10] = {'\0'};

	number_to_string((long) data->exec_counter, n_as_string, 10);

	if (errorcode == 2 || errorcode == 3)
	{
		our_printe(data->program_name);
		our_printe(": ");
		our_printe(n_as_string);
		our_printe(": ");
		our_printe(data->tokens[0]);
		if (errorcode == 2)
			our_printe(": Illegal number: ");
		else
			our_printe(": can't cd to ");
		our_printe(data->tokens[1]);
		our_printe("\n");
	}
	else if (errorcode == 127)
	{
		our_printe(data->program_name);
		our_printe(": ");
		our_printe(n_as_string);
		our_printe(": ");
		our_printe(data->command_name);
		our_printe(": not found\n");
	}
	else if (errorcode == 126)
	{
		our_printe(data->program_name);
		our_printe(": ");
		our_printe(n_as_string);
		our_printe(": ");
		our_printe(data->command_name);
		our_printe(": Permission denied\n");
	}
	return (0);
}

/**
* our_getline - function to read input
* @data: program's data
* Return: count output
*/
int our_getline(data_of_program *data)
{
	char buff[BUFFER_SIZE] = {'\0'};
	static char *array_commands[10] = {NULL};
	static char array_operators[10] = {'\0'};
	ssize_t bytes_read, i = 0;

	if (!array_commands[0] || (array_operators[0] == '&' && errno != 0) ||
		(array_operators[0] == '|' && errno == 0))
	{
		for (i = 0; array_commands[i]; i++)
		{
			free(array_commands[i]);
			array_commands[i] = NULL;
		}

		bytes_read = read(data->file_descriptor, &buff, BUFFER_SIZE - 1);
		if (bytes_read == 0)
			return (-1);

		i = 0;
		do {
			array_commands[i] = str_dup(_strtok(i ? NULL : buff, "\n;"));
			i = check_logic_ops(array_commands, i, array_operators);
		} while (array_commands[i++]);
	}
	data->input_line = array_commands[0];
	for (i = 0; array_commands[i]; i++)
	{
		array_commands[i] = array_commands[i + 1];
		array_operators[i] = array_operators[i + 1];
	}

	return (str_len(data->input_line));
}


/**
* check_logic_ops - handle && and || operators
* @array_commands: commands.
* @i: index
* @array_operators: logical operators
* Return: index of the last command
*/
int logical_operators(char *array_commands[], int i, char array_operators[])
{
	char *temp = NULL;
	int j;

	for (j = 0; array_commands[i] != NULL  && array_commands[i][j]; j++)
	{
		if (array_commands[i][j] == '&' && array_commands[i][j + 1] == '&')
		{

			temp = array_commands[i];
			array_commands[i][j] = '\0';
			array_commands[i] = str_dup(array_commands[i]);
			array_commands[i + 1] = str_dup(temp + j + 2);
			i++;
			array_operators[i] = '&';
			free(temp);
			j = 0;
		}
		if (array_commands[i][j] == '|' && array_commands[i][j + 1] == '|')
		{

			temp = array_commands[i];
			array_commands[i][j] = '\0';
			array_commands[i] = str_dup(array_commands[i]);
			array_commands[i + 1] = str_dup(temp + j + 2);
			i++;
			array_operators[i] = '|';
			free(temp);
			j = 0;
		}
	}
	return (i);
}

