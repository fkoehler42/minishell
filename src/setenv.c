/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 20:56:41 by fkoehler          #+#    #+#             */
/*   Updated: 2016/05/24 17:33:12 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_setenv(char **cmd, t_env **env_lst, int flag)
{
	int		i;

	i = 0;
	if (!cmd[0])
	{
		env_var_error(0, "setenv", "");
		return (-1);
	}
	if (flag == 0)
	{
		while (cmd[i])
		{
			if (parse_env_var(env_lst, cmd[i]) == -1)
				return (-1);
			i++;
		}
	}
	else if (flag == 1 && (parse_env_var(env_lst, cmd[i]) == -1))
		return (-1);
	return (0);
}
