#include "ourshel.h"

/**
 * osh - main shell loop
 * @inf: the parameter & return info struct
 * @argv: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int osh(info_t *inf, char **argv)
{
	ssize_t d = 0;
	int bltn_w = 0;

	while (d != -1 && bltn_w != -2)
	{
		clear_info(inf);
		if (interactive(inf))
			_puts("#ourshell$ ");
		_eputchar(BUF_FLUSH);
		r = get_input(inf);
		if (d != -1)
		{
			set_info(inf, argv);
			bltn_w = f_bltn(inf);
			if (bltn_w == -1)
				f_cmd(inf);
		}
		else if (interactive(inf))
			_putchar('\n');
		free_info(inf, 0);
	}
	write_history(inf);
	free_info(inf, 1);
	if (!interactive(inf) && inf->status)
		exit(inf->status);
	if (bltn_w == -2)
	{
		if (inf->err_num == -1)
			exit(inf->status);
		exit(inf->err_num);
	}
	return (bltn_w);
}

/**
 * f_bltn - finds a builtin command
 * @inf: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 * 	0 if builtin executed successfully,
 * 	1 if builtin found but not successful,
 * 	2 if builtin signals exit()
 */
int f_bltn(info_t *inf)
{
	int j, blt_in_w = -1;
	builtin_table bltintb[] = {
		{"exit", _ourexit},
		{"env", _ourenv},
		{"help", _ourhelp},
		{"history", _ourhistory},
		{"setenv", _oursetenv},
		{"unsetenv", _ourunsetenv},
		{"cd", _ourcd},
		{"alias", _ouralias},
		{NULL, NULL}
	};

	for (j = 0; bltintb[j].type; j++)
		if (_strcmp(info->argv[0], bltintb[j].type) == 0)
		{
			inf->line_count++;
			blt_in_w = bltintb[j].func(info);
			break;
		}
	return (blt_in_w);
}

/**
 * f_cmd - finds a command in PATH
 * @inf: the parameter & return info struct
 *
 * Return: void
 */
void f_cmd(info_t *inf)
{
	char *pth = NULL;
	int i, k;

	inf->pth = inf->argv[0];
	if (inf->linecount_flag == 1)
	{
		inf->line_count++;
		inf->linecount_flag = 0;
	}
	for (j = 0, p = 0; inf->arg[j]; j++)
		if (!is_delim(inf->arg[j], " \t\n"))
			p++;
	if (!p)
		return;

	pth = f_path(inf, _getenv(inf, "PATH="), inf->argv[0]);
	if (pth)
	{
		inf->pth = pth;
		frk_cmd(inf);
	}
	else
	{
		if ((interactive(inf) || _getenv(inf, "PATH=")
					|| inf->argv[0][0] == '/') && is_cmd(inf, inf->argv[0]))
			frk_cmd(inf);
		else if (*(inf->arg) != '\n')
		{
			inf->status = 127;
			print_error(inf, "Cannot be found\n");
		}
	}
}

/**
 * frk_cmd - forks a an exec thread to run cmd
 * @inf: the parameter & return info struct
 *
 * Return: void
 */
void frk_cmd(info_t *inf)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:Cannot perform the operation");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(inf->pth, inf->argv, get_environ(inf)) == -1)
		{
			frye_info(inf, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(inf->status));
		if (WIFEXITED(inf->status))
		{
			inf->status = WEXITSTATUS(inf->status);
			if (inf->status == 126)
				print_error(inf, "Invalid Request\n");
		}
	}
}
