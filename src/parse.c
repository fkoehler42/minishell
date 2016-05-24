/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 16:09:47 by fkoehler          #+#    #+#             */
/*   Updated: 2016/05/24 17:33:28 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <get_next_line.h>

int		binary_cmd(t_env *env_lst, char **env_tab, char **cmd)
{
	char	*bin_path;
	t_env	*home;

	bin_path = NULL;
	if (ft_strchr(cmd[0], '/') != NULL && cmd[0][0] == '~')
	{
		if (!(home = get_env_var(env_lst, "HOME")) || !home->value[0])
		{
			free_tab(env_tab);
			return (error(6));
		}
		bin_path = ft_strjoin(home->value, cmd[0] + 1);
	}
	else if (ft_strchr(cmd[0], '/') != NULL)
		bin_path = ft_strdup(cmd[0]);
	else
	{
		free(bin_path);
		return (check_bin_path(env_lst, env_tab, cmd));
	}
	if (check_bin_access(env_tab, bin_path, cmd) == 0)
		exec_error(2, bin_path);
	free_tab(env_tab);
	free(bin_path);
	return (0);
}

int		builtins_cmd(t_env *env_lst, char **cmd)
{
	char	*tmp;
	char	**env_tab;

	env_tab = NULL;
	tmp = cmd[0];
	cmd[0] = strdup_remove_quotes(cmd[0]);
	free(tmp);
	if (ft_strcmp(cmd[0], "cd") == 0)
		ft_cd(cmd, env_lst);
	else if (ft_strcmp(cmd[0], "env") == 0)
		ft_env(cmd, env_lst, 1);
	else if (ft_strcmp(cmd[0], "setenv") == 0)
		ft_setenv(++cmd, &env_lst, 0);
	else if (ft_strcmp(cmd[0], "unsetenv") == 0)
		ft_unsetenv(cmd, env_lst);
	else if (ft_strcmp(cmd[0], "exit") == 0)
		ft_exit(cmd);
	else
	{
		env_tab = make_env_tab(env_lst);
		return (binary_cmd(env_lst, env_tab, cmd));
	}
	return (0);
}

int		parse_cmd(t_env *env_lst, char *cmd)
{
	char	**cmd_tab;

	cmd_tab = strsplit_blanks_and_quotes(cmd);
	if (cmd_tab[0])
		builtins_cmd(env_lst, cmd_tab);
	free_tab(cmd_tab);
	return (0);
}

int		read_cmd(t_shell *shell)
{
	int		i;
	int		gnl;
	char	*line;
	char	**cmd_line;

	g_prompt = get_prompt(shell->env_lst);
	ft_printf("%s[%s]-> %s", CYAN, g_prompt, OFF);
	while ((gnl = get_next_line(0, &line)) == 1)
	{
		signal(SIGINT, &handle_sigint);
		i = 0;
		cmd_line = ft_strsplit(line, ';');
		while (cmd_line[i])
			parse_cmd(shell->env_lst, cmd_line[i++]);
		free_tab(cmd_line);
		free(line);
		g_prompt = get_prompt(shell->env_lst);
		ft_printf("%s[%s]-> %s", CYAN, g_prompt, OFF);
		signal(SIGINT, &handle_sigint2);
	}
	return (gnl == -1) ? error(3) : (0);
}
