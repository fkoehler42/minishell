/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_update.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 20:56:41 by fkoehler          #+#    #+#             */
/*   Updated: 2016/05/22 18:01:59 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		set_new_pwd(t_env *env_lst)
{
	char	*current_path;
	t_env	*pwd;

	current_path = NULL;
	if (!(current_path = getcwd(current_path, MAXPATHLEN)))
		return (error(5));
	if (!(pwd = get_env_var(env_lst, "PWD")))
		store_env_var(&env_lst, ft_strdup("OLDPWD"), ft_strdup(""));
	else
		store_env_var(&env_lst, ft_strdup("OLDPWD"), ft_strdup(pwd->value));
	store_env_var(&env_lst, ft_strdup("PWD"), current_path);
	return (0);
}
