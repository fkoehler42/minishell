/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/02 11:44:16 by fkoehler          #+#    #+#             */
/*   Updated: 2016/05/22 18:01:08 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	countwords(char const *s, int i, int n)
{
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == '"' && ++i)
		{
			while (s[i] && s[i] != '"')
				i++;
			n++;
		}
		else if (s[i] == '\'' && ++i)
		{
			while (s[i] && s[i] != '\'')
				i++;
			n++;
		}
		else if (s[i] != ' ' && s[i] != '\t')
		{
			while (s[i] && s[i] != ' ' && s[i] != '\t')
				i++;
			n++;
		}
		s[i] != 0 ? ++i : 0;
	}
	return (n);
}

static int	word_len(char const *s, int i)
{
	if (!s[i])
		return (i);
	if (s[i] == '\'' && ++i)
	{
		while (s[i] && s[i] != '\'')
			i++;
		s[i] != 0 ? ++i : 0;
	}
	else if (s[i] == '"' && ++i)
	{
		while (s[i] && s[i] != '"')
			i++;
		s[i] != 0 ? ++i : 0;
	}
	else
	{
		while (s[i] && s[i] != ' ' && s[i] != '\t')
			i++;
	}
	return (i);
}

char		**strsplit_blanks_and_quotes(char const *s)
{
	int		i;
	int		j;
	int		start;
	char	**array;

	i = 0;
	j = 0;
	array = (char **)malloc(sizeof(char *) * (countwords(s, 0, 0) + 1));
	if (!s || !array)
		return (NULL);
	while (s[i])
	{
		while (s[i] == ' ' || s[i] == '\t')
			i++;
		start = i;
		i = word_len(s, start);
		if (start != i)
			array[j++] = ft_strsub(s, start, (i - start));
	}
	array[j] = NULL;
	return (array);
}

char		*strdup_remove_quotes(char *str)
{
	char	*new_str;
	size_t	len;

	len = ft_strlen(str);
	if (((str[0] == '"' && str[len - 1] == '"')
		|| (str[0] == '\'' && str[len - 1] == '\'')) && ((len - 1) != 0))
		new_str = ft_strsub(str, 1, len - 2);
	else
		new_str = ft_strdup(str);
	return (new_str);
}
