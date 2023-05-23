#include "ourshell.h"

/**
 * _ourexit - exits the shell
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: exits with a given exit status
 * (0) if info.argv[0] != "exit"
 */
int _ourexit(info_t *info)
{
	int exitchecker;

	if (info->argv[1]) 
	{
		exitchecker = _err(info->argv[1]);
		if (exitchecker == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _err(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}
