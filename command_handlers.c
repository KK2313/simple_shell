#include "ourshell.h"

/**
 * main - entry point
 * @argc: arg count
 * @argv: arg vec
 * @env: values for env
 * Return: 0
 */
int main(int argc, char *argv[], char *env[])
{
	data_of_program data_struct = {NULL}, *data = &data_struct;
	char *prompt = "";

	process_data(data, argc, argv, env);

	signal(SIGINT, handle_ctrl_c);

	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO) && argc == 1)
	{
		errno = 2;
		prompt = PROMPT_MSG;
	}
	errno = 0;
	prompter(prompt, data);
	return (0);
}

/**
 * handle_ctrl_c - ..
 * @UNUSED: option of the prototype
 */
void handle_ctrl_c(int opr UNUSED)
{
	our_print("\n");
	our_print(PROMPT_MSG);
}

/**
 * process_data - load data from structure
 * @data: ..
 * @argv: args
 * @env: environ
 * @argc: args count
 */
void process_data(data_of_program *data, int argc, char *argv[], char **env)
{
	int i = 0;

	data->program_name = argv[0];
	data->input_line = NULL;
	data->command_name = NULL;
	data->exec_counter = 0;

	if (argc == 1)
		data->file_descriptor = STDIN_FILENO;
	else
	{
		data->file_descriptor = open(argv[1], O_RDONLY);
		if (data->file_descriptor == -1)
		{
			our_printe(data->program_name);
			our_printe(": 0: Can't open ");
			our_printe(argv[1]);
			our_printe("\n");
			exit(127);
		}
	}
	data->tokens = NULL;
	data->env = malloc(sizeof(char *) * 50);
	if (env)
	{
		for (; env[i]; i++)
		{
			data->env[i] = string_duplicate(env[i]);
		}
	}
	data->env[i] = NULL;
	env = data->env;

	data->alias_list = malloc(sizeof(char *) * 20);
	for (i = 0; i < 20; i++)
	{
		data->alias_list[i] = NULL;
	}
}
/**
 * prompt_sign - show prompt sign
 * @prompt: prompt
 * @data: ..
 */
void prompt_sign(char *prompt, data_of_program *data)
{
	int error_code = 0, string_length = 0;

	while (++(data->exec_counter))
	{
		our_print(prompt);
		error_code = string_length = our_getline(data);

		if (error_code == EOF)
		{
			free_data(data);
			exit(errno);
		}
		if (string_length >= 1)
		{
			remaining_alias(data);
			exp_variables(data);
			split_str(data);
			if (data->tokens[0])
			{
				error_code = execute_prog(data);
				if (error_code != 0)
					our_print_error(error_code, data);
			}
			recurrent_data_free(data);
		}
	}
}

