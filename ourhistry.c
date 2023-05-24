#include "ourshel.h"

/**
 * get_history_file - gets the history file
 * @inf: parameter struct
 *
 * Return: allocated string containg history file
 */

char *get_history_file(info_t *inf)
{
	char *cbuf, *dr;

	dr = _getenv(inf, "HOME=");
	if (!dr)
		return (NULL);
	cbuf = malloc(sizeof(char) * (_strlen(dr) + _strlen(HIST_FILE) + 2));
	if (!cbuf)
		return (NULL);
	cbuf[0] = 0;
	_strcpy(cbuf, dr);
	_strcat(cbuf, "/");
	_strcat(cbuf, HIST_FILE);
	return (cbuf);
}

/**
 * write_history - creates a file, or appends to an existing file
 * @inf: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int write_history(info_t *inf)
{
	ssize_t xy;
	char *filename = get_history_file(inf);
	list_t *apex = NULL;

	if (!filename)
		return (-1);

	xy = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (xy == -1)
		return (-1);
	for (apex = inf->history; apex; apex = apex->next)
	{
		_putsxy(apex->str, xy);
		_putxy('\n', xy);
	}
	_putxy(BUF_FLUSH, xy);
	close(xy);
	return (1);
}

/**
 * read_history - reads history from file
 * @inf: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int read_history(info_t *inf)
{
	int j, last = 0, linecount = 0;
	ssize_t xy, readlen, fsze = 0;
	struct stat st;
	char *cbuf = NULL, *filename = get_history_file(info);

	if (!filename)
		return (0);

	xy = open(filename, O_RDONLY);
	free(filename);
	if (xy == -1)
		return (0);
	if (!fstat(xy, &st))
		fsze = st.st_size;
	if (fsze < 2)
		return (0);
	cbuf = malloc(sizeof(char) * (fsze + 1));
	if (!cbuf)
		return (0);
	readlen = read(xy, cbuf, fsze);
	cbuf[fsze] = 0;
	if (readlen <= 0)
		return (free(cbuf), 0);
	close(xy);
	for (j = 0; j < fsze; j++)
		if (cbuf[j] == '\n')
		{
			cbuf[j] = 0;
			build_history_list(inf, cbuf + last, linecount++);
			last = j + 1;
		}
	if (last != j)
		build_history_list(inf, cbuf + last, linecount++);
	free(cbuf);
	inf->histcount = linecount;
	while (inf->histcount-- >= HIST_MAX)
		delete_apex_at_index(&(inf->history), 0);
	renumber_history(info);
	return (info->histcount);
}

/**
 * build_history_list - adds entry to a history linked list
 * @inf: Structure containing potential arguments. Used to maintain
 * @cbuf: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 */
int build_history_list(info_t *inf, char *cbuf, int linecount)
{
	list_t *apex = NULL;

	if (inf->history)
		apex = inf->history;
	add_apex_end(&apex, cbuf, linecount);

	if (!inf->history)
		inf->history = apex;
	return (0);
}

/**
 * renumber_history - renumbers the history linked list after changes
 * @inf: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int renumber_history(info_t *inf)
{
	list_t *apex = inf->history;
	int j = 0;

	while (apex)
	{
		apex->no = j++;
		apex = apex->next;
	}
	return (inf->histcount = j);
}
