#include "shell.h"

/**
 * hsh - main shell loop
 * @info: the parameter & return info struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(infoo_tT *info, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		c_i(info);
		if (in_a(info))
			_puts("$ ");
		e_p_c(BUF_FLUSH);
		r = g_i(info);
		if (r != -1)
		{
			s_i(info, av);
			builtin_ret = fi_pu(info);
			if (builtin_ret == -1)
				fi_cmd(info);
		}
		else if (in_a(info))
			_putchar('\n');
		f_i(info, 0);
	}
	w_h(info);
	f_i(info, 1);
	if (!in_a(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}

/**
 * fi_pu - finds a builtin command
 * @info: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int fi_pu(infoo_tT *info)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", my_e},
		{"env", m_e},
		{"help", my_h},
		{"history", m_h},
		{"setenv", m_s_e},
		{"unsetenv", m_u_s_e},
		{"cd", my_c},
		{"alias", m_l},
		{NULL, NULL}};

	for (i = 0; builtintbl[i].type; i++)
		if (str_mpP(info->argv[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[i].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * fi_cmd - finds a command in PATH
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void fi_cmd(infoo_tT *info)
{
	char *path = NULL;
	int i, k;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, k = 0; info->arg[i]; i++)
		if (!is_d(info->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = f_pa(info, g_e(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fo_cmd(info);
	}
	else
	{
		if ((in_a(info) || g_e(info, "PATH=") || info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
			fo_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			pr_er(info, "not found\n");
		}
	}
}

/**
 * fo_cmd - forks a an exec thread to run cmd
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void fo_cmd(infoo_tT *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, ge_e(info)) == -1)
		{
			f_i(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				pr_er(info, "Permission denied\n");
		}
	}
}
