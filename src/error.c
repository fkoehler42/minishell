/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/28 15:13:48 by fkoehler          #+#    #+#             */
/*   Updated: 2016/06/09 19:18:52 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		error(int errnum)
{
	if (errnum == 0)
		ft_putstr_fd("malloc: error on memory allocation\n", 2);
	else if (errnum == 1)
		ft_putstr_fd("fork: error on child proccess creation\n", 2);
	else if (errnum == 2)
		ft_putstr_fd("execve: error on child proccess execution\n", 2);
	else if (errnum == 3)
		ft_putstr_fd("minishell: error on read execution\n", 2);
	else if (errnum == 4)
	{
		ft_putstr_fd("minishell: an error occured while checking the path ", 2);
		ft_putstr_fd("sent to cd command\n", 2);
	}
	else if (errnum == 5)
	{
		ft_putstr_fd("minishell: getcwd: an error occured while checking ", 2);
		ft_putstr_fd("the actual working directory\n", 2);
		ft_putstr_fd("please send an absolute path to cd to fix the PWD\n", 2);
	}
	else if (errnum == 6)
	{
		ft_putstr_fd("minishell: environment variable HOME is not set\n", 2);
		ft_putstr_fd("please set it before using the '~/..' format\n", 2);
	}
	return (-1);
}

void	exec_error(int errnum, char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	if (errnum == 0)
		ft_putstr_fd(": permission denied\n", 2);
	else if (errnum == 1)
		ft_putstr_fd(": command not found\n", 2);
	else if (errnum == 2)
		ft_putstr_fd(": no such file or directory\n", 2);
}

void	env_var_error(int errnum, char *cmd, char *arg)
{
	if (errnum == 0)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": command requires argument\n", 2);
	}
	else if (errnum == 1)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": argument is not valid: ", 2);
		ft_putendl_fd(arg, 2);
	}
}

int		cd_cmd_error(int errnum, char *arg)
{
	if (errnum == 0)
		ft_putstr_fd("cd: environment variable HOME is not set\n", 2);
	else if (errnum == 1)
		ft_putstr_fd("cd: environment variable OLDPWD is not set\n", 2);
	else if (errnum == 2)
		ft_putstr_fd("cd: too many arguments\n", 2);
	else if (errnum == 3 || errnum == 4 || errnum == 5)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(arg, 2);
	}
	else if (errnum == 6)
	{
		ft_putstr_fd("cd: chdir: an error occured while changing the ", 2);
		ft_putstr_fd("current directory\n", 2);
	}
	if (errnum == 3)
		ft_putstr_fd(" : permission denied\n", 2);
	else if (errnum == 4)
		ft_putstr_fd(" : no such file or directory\n", 2);
	else if (errnum == 5)
		ft_putstr_fd(" : not a directory\n", 2);
	return (-1);
}

int		env_cmd_error(int errnum, int flag)
{
	if (errnum == 0)
	{
		ft_putstr_fd("env: illegal option -- ", 2);
		ft_putchar_fd(flag, 2);
	}
	else if (errnum == 1)
	{
		ft_putstr_fd("env: option requires an argument -- ", 2);
		ft_putchar_fd(flag, 2);
	}
	else if (errnum == 2)
		ft_putstr_fd("env: no option specified", 2);
	ft_putstr_fd("\nusage: env [-i] [-u name] [name=value] ", 2);
	ft_putstr_fd("[utility [argument(s)]]\n", 2);
	return (-1);
}
