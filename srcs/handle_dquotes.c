/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dquotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmalcom <qmalcom@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 18:01:14 by qmalcom           #+#    #+#             */
/*   Updated: 2020/12/08 10:50:42 by qmalcom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	is_join_dq(char *str, int *i, t_currword *currword)
{
	if (str[*i] != '\"')
	{
		currword->ret_to_dq = 1;
		currword->join = 1;
	}
	else if (str[*i] == '\"' && str[*i + 1] && str[*i + 1] != ' ')
	{
		*i += 1;
		currword->ret_to_dq = 0;
		currword->join = 1;
	}
	else
	{
		*i += 1;
		currword->ret_to_dq = 0;
		currword->join = 0;
	}
}

int		is_env_var(char *str, int *i, t_currword *currword)
{
	if (str[*i] == '$' && str[*i + 1] && (ft_isalpha(str[*i + 1]) ||
												str[*i + 1] == '_'))
	{
		currword->start = *i + 1;
		*i += 1;
		currword->spec_symb = 2;
		while (str[*i] && (ft_isalpha(str[*i]) || ft_isdigit(str[*i]) ||
													str[*i] == '_'))
			*i += 1;
		currword->len = *i - currword->start;
		is_join_dq(str, i, currword);
		return (1);
	}
	return (0);
}

int		is_only_dollar(char *str, int *i, t_currword *currword)
{
	if (str[*i] == '$' && !ft_isalpha(str[*i + 1]) && str[*i + 1] != '_')
	{
		currword->start = *i;
		currword->spec_symb = 0;
		*i += 1;
		currword->len = 1;
		is_join_dq(str, i, currword);
		return (1);
	}
	return (0);
}

int		is_reg_symb(char *str, int *i, t_currword *currword)
{
	if (str[*i] != '$' && str[*i] != '\"' && str[*i] != '\\')
	{
		currword->start = *i;
		*i += 1;
		currword->spec_symb = 0;
		while (str[*i] != '$' && str[*i] != '\"' && str[*i] != '\\')
			*i += 1;
		currword->len = *i - currword->start;
		is_join_dq(str, i, currword);
		return (1);
	}
	return (0);
}

int		is_bslash(char *str, int *i, t_currword *currword)
{
	if (str[*i] == '\\')
	{
		if (str[*i + 1] == '\\' || str[*i + 1] == '$' || str[*i + 1] == '\"')
		{
			*i += 1;
			currword->start = *i;
			currword->len = 1;
			currword->spec_symb = 0;
			*i += 1;
			is_join_dq(str, i, currword);
			return (1);
		}
		else
		{
			currword->start = *i;
			*i += 1;
			currword->len = 1;
			currword->spec_symb = 0;
			is_join_dq(str, i, currword);
			return (1);
		}
	}
	return (0);
}
