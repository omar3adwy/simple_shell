#include "shell.h"

/**
 * my_e - exits the shell
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: exits with a given exit status
 *         (0) if info.argv[0] != "exit"
 */
int my_e(infoo_tT *info)
{
	int exitcheck;

	if (info->argv[1]) /* If there is an exit arguement */
	{
		exitcheck = er_a(info->argv[1]);
		if (exitcheck == -1)
		{
			info->status = 2;
			pr_er(info, "Illegal number: ");
			e_pu(info->argv[1]);
			e_p_c('\n');
			return (1);
		}
		info->err_num = er_a(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * my_c - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int my_c(infoo_tT *info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = g_e(info, "HOME=");
		if (!dir)
			chdir_ret = /* TODO: what should this be? */
				chdir((dir = g_e(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (str_mpP(info->argv[1], "-") == 0)
	{
		if (!g_e(info, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(g_e(info, "OLDPWD=")), _putchar('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((dir = g_e(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		pr_er(info, "can't cd to ");
		e_pu(info->argv[1]), e_p_c('\n');
	}
	else
	{
		s_e(info, "OLDPWD", g_e(info, "PWD="));
		s_e(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * my_h - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int my_h(infoo_tT *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array); /* temp att_unused workaround */
	return (0);
}
