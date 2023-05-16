#include "ourshell.h"
	
/**
 * handle_cmd - finds, calls, and runs the execution of a cmd.
 * @prog_name: The name of the call.
 * @history: The history number of the call.
 * @ret_exe: The return value of the last executed cmd
 *
 * Return: When an EOF is(-2).
 *         When the input cannot be tokenized - -1
 *         When the exit value of the last executed cmd is o/w
 */

int handle_cmd(char *prog_name, int *history, int *ret_exe)
{
	int rtn, index;
	char **args, *cmd_line = NULL, **front;

	cmd_line = get_args(cmd_line, ret_exe);
	if (!cmd_line)
		return (EOF);

	args = _strtok(cmd_line, " ");
	free(cmd_line);
	if (!args)
		return (0);
	front = args;

	for (index = 0; args[index]; index++)
	{
		if (_strncmp(args[index], ";", 1) == 0)
		{
			free(args[index]);
			args[index] = NULL;
			rtn = call_args(args, front,prog_ name, history, ret_exe);
			args = &args[++index];
			index = 0;
		}
	}

	rtn = call_args(args, front, prog_name, history, ret_exe);

	free(front);
	return (rtn);
}
