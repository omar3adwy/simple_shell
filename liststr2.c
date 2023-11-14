#include "shell.h"

/**
 * l_l - determines length of linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t l_l(const listt_T *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * l_t_s - returns an array of strings of the list->str
 * @head: pointer to first node
 *
 * Return: array of strings
 */
char **l_t_s(listt_T *head)
{
	listt_T *node = head;
	size_t i = l_l(head), j;
	char **strs;
	char *str;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(str_leE(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = str_py(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}

/**
 * p_l - prints all elements of a listt_T linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t p_l(const listt_T *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(co_n(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * n_s_w - returns node whose string starts with prefix
 * @node: pointer to list head
 * @prefix: string to match
 * @c: the next character after prefix to match
 *
 * Return: match node or null
 */
listt_T *n_s_w(listt_T *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = s_wiI(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * g_n_i - gets the index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t g_n_i(listt_T *head, listt_T *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}
