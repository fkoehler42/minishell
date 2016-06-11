/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 20:56:41 by fkoehler          #+#    #+#             */
/*   Updated: 2016/06/11 17:19:39 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/stat.h>

static int	free_path_error_return(char *path)
{
	free(path);
	return (-1);
}

static void	put_pwd(t_env *home, char *path)
{
	int		i;

	i = 0;
	if (!home || !home->value[0])
		ft_putendl(path);
	else
	{
		while (home->value[i] && path[i] && home->value[i] == path[i])
			i++;
		if (!home->value[i])
			ft_printf("~%s\n", path + i);
		else
			ft_putendl(path);
	}
}

int			ft_cd(char **cmd, t_env *env_lst)
{
	t_env	*home;
	char	*path;

	home = get_env_var(env_lst, "HOME");
	path = NULL;
	if ((!home || !home->value[0]) && (!cmd[1] || cmd[1][0] == '~'))
		return (cd_cmd_error(0, ""));
	if (cmd[1] && cmd[2])
		return (cd_cmd_error(2, ""));
	if (!(path = get_path_to_search(cmd[1], home, env_lst)))
		return (-1);
	if (check_path(path) != 0)
		return (free_path_error_return(path));
	if (chdir(path) != 0)
		return (free_path_error_return(path));
	if (cmd[1] && ft_strcmp(cmd[1], "-") == 0)
		put_pwd(home, path);
	if (set_new_pwd(env_lst) == -1)
		return (free_path_error_return(path));
	free(path);
	return (0);
}

int			check_path(char *path)
{
	struct stat	buf;

	if (stat(path, &buf) < 0)
	{
		if (access(path, F_OK) != 0)
			return (cd_cmd_error(4, path));
		if (access(path, X_OK) != 0)
			return (cd_cmd_error(3, path));
		return (error(4));
	}
	if (!(S_ISDIR(buf.st_mode)))
		return (cd_cmd_error(5, path));
	if (access(path, X_OK) != 0)
		return (cd_cmd_error(3, path));
	return (0);
}

char		*get_path_to_search(char *cmd, t_env *home, t_env *env_lst)
{
	char	*path;
	t_env	*oldpwd;

	path = NULL;
	oldpwd = NULL;
	if (!cmd)
		path = ft_strdup(home->value);
	else if (ft_strcmp(cmd, "-") == 0)
	{
		if (!(oldpwd = get_env_var(env_lst, "OLDPWD")) || !oldpwd->value[0])
			cd_cmd_error(1, "");
		else
			path = ft_strdup(oldpwd->value);
	}
	else if (cmd[0] == '~')
	{
		if (!(path = ft_strjoin(home->value, cmd + 1)))
			cd_cmd_error(0, "");
	}
	else
		path = strdup_remove_quotes(cmd);
	return (path);
}
