#include "shell.h"

/**
 * g_h_f - gets the history file
 * @info: parameter struct
 *
 * Return: allocated string containg history file
 */

char *g_h_f(infoo_tT *info)
{
	char *buf, *dir;

	dir = g_e(info, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (str_leE(dir) + str_leE(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	str_py(buf, dir);
	str_catT(buf, "/");
	str_catT(buf, HIST_FILE);
	return (buf);
}

/**
 * w_h - creates a file, or appends to an existing file
 * @info: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int w_h(infoo_tT *info)
{
	ssize_t fd;
	char *filename = g_h_f(info);
	listt_T *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		pu_fd(node->str, fd);
		p_fd('\n', fd);
	}
	p_fd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * r_h - reads history from file
 * @info: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int r_h(infoo_tT *info)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = g_h_f(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			b_h_l(info, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		b_h_l(info, buf + last, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		d_n_a_i(&(info->history), 0);
	r_hi(info);
	return (info->histcount);
}

/**
 * b_h_l - adds entry to a history linked list
 * @info: Structure containing potential arguments. Used to maintain
 * @buf: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 */
int b_h_l(infoo_tT *info, char *buf, int linecount)
{
	listt_T *node = NULL;

	if (info->history)
		node = info->history;
	a_n_e(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * r_hi - renumbers the history linked list after changes
 * @info: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int r_hi(infoo_tT *info)
{
	listt_T *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (info->histcount = i);
}
