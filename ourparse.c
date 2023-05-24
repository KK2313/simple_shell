#include "ourshel.h"

/**
 * execmd - determines if a file is an executable command
 * @info: the info struct
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int execmd(info_t *info, char *path)
{
	struct stat jk;

	(void)info;
	if (!path || stat(path, &jk))
		return (0);

	if (jk.jk_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dchars - duplicates characters
 * @pstr: the PATH string
 * @st: starting index
 * @stp: stopping index
 *
 * Return: pointer to new buffer
 */
char *dchars(char *pstr, int st, int stp)
{
	static char buf[1024];
	int u = 0, v = 0;

	for (v = 0, u = start; u < stop; u++)
		if (pathstr[u] != ':')
			buf[v++] = pstr[u];
	buf[v] = 0;
	return (buf);
}

/**
 * fpath - finds this cmd in the PATH string
 * @info: the info struct
 * @pstr: the PATH string
 * @cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *fpath(info_t *info, char *pstr, char *cmd)
{
	int u = 0, ipos = 0;
	char *path;

	if (!pstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pstr[u] || pstr[u] == ':')
		{
			path = dchars(pstr, ipos, u);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			if (!pstr[u])
				break;
			ipos = u;
		}
		u++;
	}
	return (NULL);
}
