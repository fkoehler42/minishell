/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_sig.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 11:50:45 by fkoehler          #+#    #+#             */
/*   Updated: 2016/05/21 15:11:53 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint(int signum)
{
	(void)signum;
}

void	handle_sigint2(int signum)
{
	(void)signum;
	ft_printf("\n%s[%s]-> %s", CYAN, g_prompt, OFF);
}
