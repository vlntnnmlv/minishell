/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarguri <rmarguri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 15:39:39 by rmarguri          #+#    #+#             */
/*   Updated: 2020/12/03 18:50:37 by rmarguri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int				check_quote(char *str, int i)
{
	if (str[i] && (str[i] == '\''))
		return (1);
	return (0);
}

int				check_dquote(char *str, int i)
{
	if (str[i] && (str[i] == '\"'))
		return (1);
	return (0);
}

static int		check_bslash(char *str, int len)
{
	int	bslash;

	bslash = 0;
	while (--len >= 0 && str[len] == '\\')
		bslash += 1;
	if (bslash % 2 == 0)
	{
		write(1, CONTINUE, 2);
		return (1);
	}
	return (0);
}

/*
** searching | from behind of str
** 1. skip spaces
** 2. it's | if there is even number of \ next to |
** so \| or \\\| is not open pipe
** but \\| or \\\\| is open pipe.
** if string is "|" - no need to wait command
*/

int				check_pipe(char *str)
{
	int	len;

	if (!str)
		return (0);
	len = ft_strlen(str) - 1;
	while (len >= 0 && str[len] == ' ')
		len -= 1;
	if (len >= 0 && str[len] == '|')
	{
		if (len == 0)
			return (0);
		if (check_bslash(str, len))
			return (1);
	}
	return (0);
}

int				find_quotes(char *str, int gnl_res)
{
	int i;
	int quotes;
	int dquotes;

	i = -1;
	quotes = 0;
	dquotes = 0;
	if (!gnl_res)
		return (1);
	while (str[++i])
	{
		if (str[i] == '\'' && dquotes % 2 == 0)
			quotes += 1;
		if (str[i] == '\"' && quotes % 2 == 0)
			dquotes += 1;
		if (str[i] == '\\' && (check_quote(str, i + 1) || \
		check_dquote(str, i + 1)) && quotes % 2 == 0)
			i += 1;
	}
	if (quotes % 2 == 1 || dquotes % 2 == 1)
	{
		write(1, CONTINUE, 2);
		return (1);
	}
	return (0);
}
