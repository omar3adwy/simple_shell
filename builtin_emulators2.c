#include "shell.h"

/**
 * m_h - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int m_h(infoo_tT *info)
{
	p_l(info->history);
	return (0);
}

/**
 * unset_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(infoo_tT *info, char *str)
{
	char *p, c;
	int ret;

	p = str_hr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = d_n_a_i(&(info->alias),
				  g_n_i(info->alias, n_s_w(info->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * set_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(infoo_tT *info, char *str)
{
	char *p;

	p = str_hr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (a_n_e(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(listt_T *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = str_hr(node->str, '=');
		for (a = node->str; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * m_l - mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int m_l(infoo_tT *info)
{
	int i = 0;
	char *p = NULL;
	listt_T *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = str_hr(info->argv[i], '=');
		if (p)
			set_alias(info, info->argv[i]);
		else
			print_alias(n_s_w(info->alias, info->argv[i], '='));
	}

	return (0);
}
