#include "ourshel.h"

/**
 * main - entry point
 * @ac: arg count
 * @argv: arg vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int ac, char **argv)
{
	info_t info[] = { INFO_INIT };
	int xy = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (xy)
			: "r" (xy));

	if (ac == 2)
	{
		xy = open(argv[1], O_RDONLY);
		if (xy == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(av[0]);
				_eputs(": 0: Can't open ");
				_eputs(argv[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readxy = xy;
	}

	populate_env_list(info);
	read_history(info);
	hsh(info, argv);
	return (EXIT_SUCCESS);
}
