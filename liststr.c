#include "shell.h"

/**
 * a_n - adds a node to the start of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
listt_T *a_n(listt_T **head, const char *str, int num)
{
	listt_T *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(listt_T));
	if (!new_head)
		return (NULL);
	me_s((void *)new_head, 0, sizeof(listt_T));
	new_head->num = num;
	if (str)
	{
		new_head->str = str_du(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}

/**
 * a_n_e - adds a node to the end of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
listt_T *a_n_e(listt_T **head, const char *str, int num)
{
	listt_T *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(listt_T));
	if (!new_node)
		return (NULL);
	me_s((void *)new_node, 0, sizeof(listt_T));
	new_node->num = num;
	if (str)
	{
		new_node->str = str_du(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}

/**
 * p_l_s - prints only the str element of a listt_T linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t p_l_s(const listt_T *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * d_n_a_i - deletes node at given index
 * @head: address of pointer to first node
 * @index: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int d_n_a_i(listt_T **head, unsigned int index)
{
	listt_T *node, *prev_node;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (i == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * f_l - frees all nodes of a list
 * @head_ptr: address of pointer to head node
 *
 * Return: void
 */
void f_l(listt_T **head_ptr)
{
	listt_T *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}
