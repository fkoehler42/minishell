/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/28 16:19:47 by fkoehler          #+#    #+#             */
/*   Updated: 2016/05/22 16:57:16 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_env_var(char *env_var, char *cmd)
{
	int		i;

	i = 0;
	if (!env_var[i] || env_var[i] == '=')
	{
		env_var_error(1, cmd, env_var);
		return (-1);
	}
	while (env_var[i] && env_var[i] != '=')
	{
		if (!ft_isalnum(env_var[i]) && env_var[i] != '_')
		{
			env_var_error(1, cmd, env_var);
			return (-1);
		}
		i++;
	}
	return (0);
}

t_env	*get_env_var(t_env *env_lst, char *var)
{
	t_env	*env_var;

	if (!env_lst)
		return (NULL);
	env_var = env_lst;
	while (env_var && (ft_strcmp(env_var->var, var) != 0))
		env_var = env_var->next;
	if (!env_var)
		return (NULL);
	return (env_var);
}

int		store_env_var(t_env **env_lst, char *var, char *value)
{
	t_env	*new;
	t_env	*tmp;

	if ((tmp = get_env_var(*env_lst, var)) != NULL)
	{
		free(var);
		free(tmp->value);
		tmp->value = value;
		return (0);
	}
	if (!(new = (t_env *)malloc(sizeof(t_env))))
		return (error(0));
	new->var = var;
	new->value = value;
	new->next = NULL;
	if (!(*env_lst))
		*env_lst = new;
	else
	{
		tmp = *env_lst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (0);
}

int		parse_env_var(t_env **env_lst, char *env_var)
{
	int		i;
	char	*var;
	char	*value;
	char	*dup_var;

	value = NULL;
	dup_var = strdup_remove_quotes(env_var);
	if (check_env_var(dup_var, "setenv") == -1)
	{
		free(dup_var);
		return (-1);
	}
	if ((i = ft_strchr_index(dup_var, '=')) == -1)
		var = dup_var;
	else
	{
		var = ft_strsub(dup_var, 0, i);
		if (dup_var[i + 1])
			value = ft_strsub(dup_var, i + 1, (ft_strlen(dup_var) - i - 1));
		free(dup_var);
	}
	if (!value)
		value = ft_strdup("");
	return (store_env_var(env_lst, var, value));
}
