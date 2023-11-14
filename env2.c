#include "shell.h"

/**
 * ge_e - returns the string array copy of our environ
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **ge_e(infoo_tT *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = l_t_s(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * u_s_e - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @var: the string env var property
 */
int u_s_e(infoo_tT *info, char *var)
{
	listt_T *node = info->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = s_wiI(node->str, var);
		if (p && *p == '=')
		{
			info->env_changed = d_n_a_i(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->env_changed);
}

/**
 * s_e - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string env var property
 * @value: the string env var value
 *  Return: Always 0
 */
int s_e(infoo_tT *info, char *var, char *value)
{
	char *buf = NULL;
	listt_T *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(str_leE(var) + str_leE(value) + 2);
	if (!buf)
		return (1);
	str_py(buf, var);
	str_catT(buf, "=");
	str_catT(buf, value);
	node = info->env;
	while (node)
	{
		p = s_wiI(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	a_n_e(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}
