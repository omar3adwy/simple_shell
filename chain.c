#include "shell.h"

/**
 * ischa - test if current char in buffer is a chain delimeter
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int ischa(infoo_tT *info, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';') /* found end of this command */
	{
		buf[j] = 0; /* replace semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * che_cha - checks we should continue chaining based on last status
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 * @i: starting position in buf
 * @len: length of buf
 *
 * Return: Void
 */
void che_cha(infoo_tT *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * rep_al - replaces an aliases in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int rep_al(infoo_tT *info)
{
	int i;
	listt_T *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = n_s_w(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = str_hr(node->str, '=');
		if (!p)
			return (0);
		p = str_du(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * rep_v - replaces vars in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int rep_v(infoo_tT *info)
{
	int i = 0;
	listt_T *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!str_mpP(info->argv[i], "$?"))
		{
			rep_s(&(info->argv[i]),
				  str_du(co_n(info->status, 10, 0)));
			continue;
		}
		if (!str_mpP(info->argv[i], "$$"))
		{
			rep_s(&(info->argv[i]),
				  str_du(co_n(getpid(), 10, 0)));
			continue;
		}
		node = n_s_w(info->env, &info->argv[i][1], '=');
		if (node)
		{
			rep_s(&(info->argv[i]),
				  str_du(str_hr(node->str, '=') + 1));
			continue;
		}
		rep_s(&info->argv[i], str_du(""));
	}
	return (0);
}

/**
 * rep_s - replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int rep_s(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
