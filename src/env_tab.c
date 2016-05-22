/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tab.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/28 16:19:47 by fkoehler          #+#    #+#             */
/*   Updated: 2016/05/12 15:33:53 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**make_env_tab(t_env *env_lst)
{
	int		i;
	char	*tmp;
	t_env	*tmp_env;
	char	**tab;

	i = 0;
	if (!env_lst)
		return (NULL);
	tmp_env = env_lst;
	while (tmp_env && ++i)
		tmp_env = tmp_env->next;
	if (!(tab = (char **)malloc(sizeof(char *) * (i + 1))))
		error(0);
	tmp_env = env_lst;
	i = 0;
	while (tmp_env)
	{
		tmp = ft_strjoin(tmp_env->var, "=");
		tab[i] = ft_strjoin(tmp, tmp_env->value);
		free(tmp);
		tmp_env = tmp_env->next;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}
