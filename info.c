#include "shell.h"

/**
 * c_i - initializes infoo_tT struct
 * @info: struct address
 */
void c_i(infoo_tT *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * s_i - initializes infoo_tT struct
 * @info: struct address
 * @av: argument vector
 */
void s_i(infoo_tT *info, char **av)
{
	int i = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = str_tTT(info->arg, " \t");
		if (!info->argv)
		{

			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = str_du(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		rep_al(info);
		rep_v(info);
	}
}

/**
 * f_i - frees infoo_tT struct fields
 * @info: struct address
 * @all: true if freeing all fields
 */
void f_i(infoo_tT *info, int all)
{
	f_f(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			f_l(&(info->env));
		if (info->history)
			f_l(&(info->history));
		if (info->alias)
			f_l(&(info->alias));
		f_f(info->environ);
		info->environ = NULL;
		b_f((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}
