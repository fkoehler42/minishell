/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_display.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/14 20:01:15 by fkoehler          #+#    #+#             */
/*   Updated: 2016/05/24 18:46:12 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_relative_path(t_env *home, t_env *pwd)
{
	int		i;
	char	*prompt;

	i = 0;
	while (home->value[i] && pwd->value[i]
			&& home->value[i] == pwd->value[i])
		i++;
	if (!home->value[i])
		prompt = ft_strjoin("~", (pwd->value + i));
	else if (!pwd->value[i] || access(pwd->value, F_OK) == 0)
		prompt = ft_strdup(pwd->value);
	else
		prompt = ft_strdup("$");
	return (prompt);
}

char		*get_prompt(t_env *env_lst)
{
	t_env	*home;
	t_env	*pwd;
	t_env	*oldpwd;

	if (g_prompt)
		free(g_prompt);
	g_prompt = NULL;
	home = get_env_var(env_lst, "HOME");
	pwd = get_env_var(env_lst, "PWD");
	oldpwd = get_env_var(env_lst, "OLDPWD");
	if (!pwd || !pwd->value[0])
		g_prompt = ft_strdup("$");
	else if (!home || !home->value[0])
		g_prompt = ft_strdup(pwd->value);
	else
		g_prompt = get_relative_path(home, pwd);
	return (g_prompt);
}
