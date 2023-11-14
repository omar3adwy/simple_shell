#include "shell.h"

/**
 * m_e - prints the current environment
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int m_e(infoo_tT *info)
{
	p_l_s(info->env);
	return (0);
}

/**
 * g_e - gets the value of an environ variable
 * @info: Structure containing potential arguments. Used to maintain
 * @name: env var name
 *
 * Return: the value
 */
char *g_e(infoo_tT *info, const char *name)
{
	listt_T *node = info->env;
	char *p;

	while (node)
	{
		p = s_wiI(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * m_s_e - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int m_s_e(infoo_tT *info)
{
	if (info->argc != 3)
	{
		e_pu("Incorrect number of arguements\n");
		return (1);
	}
	if (s_e(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * m_u_s_e - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int m_u_s_e(infoo_tT *info)
{
	int i;

	if (info->argc == 1)
	{
		e_pu("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		u_s_e(info, info->argv[i]);

	return (0);
}

/**
 * p_e_l - populates env linked list
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int p_e_l(infoo_tT *info)
{
	listt_T *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		a_n_e(&node, environ[i], 0);
	info->env = node;
	return (0);
}
