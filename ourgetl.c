#include "ourshel.h"

/**
 * input_buf - buffers chained commands
 * @inf: parameter struct
 * @cbuf: address of buffer
 * @length: address of len var
 *
 * Return: bytes read
 */
ssize_t input_buf(info_t *inf, char **cbuf, size_t *length)
{
	ssize_t s = 0;
	size_t length_w = 0;

	if (!*length)
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*cbuf);
		*cbuf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		s = getline(cbuf, &length_w, stdin);
#else
		s = _getline(inf, cbuf, &length_w);
#endif
		if (s > 0)
		{
			if ((*cbuf)[s - 1] == '\n')
			{
				(*cbuf)[s - 1] = '\0'; /* removes the trailing newline */
				s--;
			}
			inf->linecount_flag = 1;
			remove_comments(*cbuf);
			build_history_list(inf, *cbuf, inf->histcount++);
			{
				*length = s;
				inf->cmd_cbuf = cbuf;
			}
		}
	}
	return (s);
}

/**
 * get_input - gets a line minus the newline
 * @inf: parameter struct
 *
 * Return: bytes read
 */
ssize_t get_input(info_t *inf)
{
	static char *cbuf; /* the ';' command chain buffer */
	static size_t j, z, length;
	ssize_t s = 0;
	char **cbuf_w = &(inf->arg), *w;

	_putchar(BUF_FLUSH);
	s = input_buf(inf, &cbuf, &length);
	if (s == -1) /* EOF */
		return (-1);
	if (length) /* we have commands left in the chain buffer */
	{
		z = j; /* init new iterator to current buf position */
		w = cbuf + j; /* get pointer for return */

		check_chain(inf, cbuf, &z, j, length);
		while (z < length) /* iterate to semicolon or end */
		{
			if (is_chain(inf, cbuf, &z))
				break;
			z++;
		}

		j = z + 1; /* increment past nulled ';'' */
		if (j >= length) /* reached end of buffer? */
		{
			j = length = 0; /* reset position and length */
			inf->cmd_buf_type = CMD_NORM;
		}

		*cbuf_w = w; /* pass back pointer to current command position */
		return (_strlen(w)); /* return length of current command */
	}

	*cbuf_w = cbuf; /* else not a chain, pass back buffer from _getline() */
	return (s); /* return length of buffer from _getline() */
}

/**
 * read_buf - reads a buffer
 * @inf: parameter struct
 * @cbuf: buffer
 * @j: size
 *
 * Return: s
 */
ssize_t read_buf(info_t *inf, char *cbuf, size_t *j)
{
	ssize_t s = 0;

	if (*j)
		return (0);
	s = read(inf->readxy, cbuf, READ_BUF_SIZE);
	if (s >= 0)
		*j = s;
	return (s);
}

/**
 * _getline - gets the next line of input from STDIN
 * @inf: parameter struct
 * @pointer: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: v
 */
int _getline(info_t *inf, char **pointer, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t j, len;
	size_t r;
	ssize_t s = 0, x = 0;
	char *w = NULL, *new_w = NULL, *g;

	w = *pointer;
	if (w && length)
		x = *length;
	if (j == len)
		j = len = 0;

	s = read_buf(inf, cbuf, &len);
	if (s == -1 || (s == 0 && len == 0))
		return (-1);

	g = _strchr(cbuf + j, '\n');
	r = g ? 1 + (unsigned int)(g - cbuf) : len;
	new_w = _realloc(w, x, x ? x + r : r + 1);
	if (!new_w) /* MALLOC FAILURE! */
		return (w ? free(w), -1 : -1);

	if (x)
		_strncat(new_w, cbuf + j, r - i);
	else
		_strncpy(new_w, cbuf + j, r - i + 1);

	x += r - i;
	j = r;
	w = new_w;

	if (length)
		*length = x;
	*pointer = w;
	return (x);
}

/**
 * sigintHandler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("#ourshell$ ");
	_putchar(BUF_FLUSH);
}
