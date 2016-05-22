/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/03 13:02:52 by fkoehler          #+#    #+#             */
/*   Updated: 2016/05/22 16:29:01 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		execute_bin(char *bin, char **args, char **env)
{
	int		status;
	pid_t	pid;

	status = 0;
	if ((pid = fork()) < 0)
		error(1);
	if (pid == 0)
	{
		if (execve(bin, args, env) < 0)
		{
			error(2);
			exit(EXIT_FAILURE);
		}
	}
	else if (pid > 0)
		waitpid(pid, &status, 0);
	return (0);
}

int		check_bin_access(char **env_tab, char *bin_path, char **cmd)
{
	if (access(bin_path, F_OK) == 0)
	{
		if (access(bin_path, X_OK) == 0)
			execute_bin(bin_path, cmd, env_tab);
		else
		{
			exec_error(0, cmd[0]);
			return (-1);
		}
		return (1);
	}
	return (0);
}

char	**get_paths(t_env *env_lst)
{
	int		i;
	t_env	*tmp_env;
	char	*tmp_path;
	char	**paths;

	i = 0;
	tmp_env = env_lst;
	while (tmp_env && (ft_strcmp(tmp_env->var, "PATH") != 0))
		tmp_env = tmp_env->next;
	if (!tmp_env)
		paths = ft_strsplit(DEFAULT_PATH, ':');
	else
		paths = ft_strsplit(tmp_env->value, ':');
	while (paths[i])
	{
		tmp_path = paths[i];
		paths[i] = ft_strjoin(tmp_path, "/");
		free(tmp_path);
		i++;
	}
	return (paths);
}

int		check_bin_path(t_env *env_lst, char **env_tab, char **cmd)
{
	int		i;
	int		j;
	char	*bin_path;
	char	**paths;

	i = 0;
	paths = get_paths(env_lst);
	while (paths[i])
	{
		bin_path = NULL;
		bin_path = ft_strjoin(paths[i], cmd[0]);
		if ((j = check_bin_access(env_tab, bin_path, cmd) != 0))
		{
			free(bin_path);
			break ;
		}
		free(bin_path);
		i++;
	}
	free_tab(paths);
	free_tab(env_tab);
	if (j == 0)
		exec_error(1, cmd[0]);
	return (0);
}
