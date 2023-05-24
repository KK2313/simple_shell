#include "ourshel.h"

/**
 * clear_info - initializes info_t struct
 * @inf: struct address
 */
void clear_info(info_t *inf)
{
	inf->arg = NULL;
	inf->argv = NULL;
	inf->path = NULL;
	inf->argc = 0;
}

/**
 * set_info - initializes info_t struct
 * @inf: struct address
 * @argv: argument vector
 */
void set_info(info_t *inf, char **argv)
{
	int j = 0;

	inf->fname = argv[0];
	if (inf->arg)
	{
		inf->argv = stw(inf->arg, " \t");
		if (!inf->argv)
		{
			inf->argv = malloc(sizeof(char *) * 2);
			if (inf->argv)
			{
				inf->argv[0] = _strdup(info->arg);
				inf->argv[1] = NULL;
			}
		}
		for (j = 0; inf->argv && inf->argv[j]; j++);
		inf->argc = j;

		replace_alias(inf);
		replace_vars(inf);
	}
}

/**
 * free_info - frees info_t struct fields
 * @inf: struct address
 * @al: true if freeing all fields
 */
void free_info(info_t *inf, int al)
{
	ffree(inf->argv);
	inf->argv = NULL;
	inf->path = NULL;
	if (al)
	{
		if (!inf->cmd_buf)
			free(inf->arg);
		if (inf->env)
			free_list(&(inf->env));
		if (inf->history)
			free_list(&(inf->history));
		if (inf->alias)
			free_list(&(inf->alias));
		ffree(inf->environ);
			inf->environ = NULL;
		bfree((void **)inf->cmd_cbuf);
		if (inf->readxy > 2)
			close(inf->readxy);
		_putchar(BUF_FLUSH);
	}
}
