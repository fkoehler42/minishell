/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 20:56:41 by fkoehler          #+#    #+#             */
/*   Updated: 2016/05/12 18:40:32 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_setenv(char **cmd, t_env **env_lst)
{
	int		i;

	i = 0;
	if (!cmd[0])
	{
		env_var_error(0, "setenv", "");
		return (-1);
	}
	while (cmd[i])
	{
		if (parse_env_var(env_lst, cmd[i]) == -1)
			return (-1);
		i++;
	}
	return (0);
}
