/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/09 14:05:34 by fkoehler          #+#    #+#             */
/*   Updated: 2016/05/11 20:20:45 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env_var(t_env *env_var)
{
	free(env_var->var);
	free(env_var->value);
	free(env_var);
}

void	free_env_lst(t_env **env_lst)
{
	t_env *tmp1;
	t_env *tmp2;

	if (!env_lst || !(*env_lst))
		return ;
	tmp1 = *env_lst;
	while (tmp1)
	{
		tmp2 = (tmp1)->next;
		free_env_var(tmp1);
		tmp1 = tmp2;
	}
	*env_lst = NULL;
}
