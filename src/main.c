/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 11:50:45 by fkoehler          #+#    #+#             */
/*   Updated: 2016/06/09 10:32:34 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		init_shell_struct(t_shell *shell, char **av)
{
	shell->args = av;
	shell->env_lst = NULL;
	return (0);
}

int		main(int ac, char **av, char **environ)
{
	int			i;
	t_shell		shell;

	i = 0;
	ac += 0;
	signal(SIGINT, &handle_sigint2);
	signal(SIGTSTP, SIG_IGN);
	init_shell_struct(&shell, av);
	while (environ[i])
	{
		parse_env_var(&shell.env_lst, environ[i]);
		i++;
	}
	read_cmd(&shell);
	return (0);
}
