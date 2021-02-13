/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_currword_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmalcom <qmalcom@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 05:02:17 by qmalcom           #+#    #+#             */
/*   Updated: 2020/12/07 15:00:35 by qmalcom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		fill_currword(t_currword *currword, int *i, int len)
{
	currword->start = *i;
	currword->len = len;
	currword->join = 0;
	*i += len;
	return (1);
}

int		fill_spec_symb(t_currword *currword, int *i, int len)
{
	currword->start = *i;
	currword->len = len;
	currword->join = 0;
	currword->spec_symb = 1;
	*i += len;
	return (1);
}

int		is_just_dollar(char *str, int *i, t_currword *currword)
{
	if (!str[*i] || !isn_spec_symb(str, i))
	{
		if (str[*i] == '\'' || str[*i] == '\"' || str[*i] == '$')
		{
			currword->join = 1;
			currword->spec_symb = 2;
		}
		else
			currword->join = 0;
		return (1);
	}
	return (0);
}

int		get_envvar_name(char *str, int *i, t_currword *currword)
{
	currword->start = *i;
	currword->len = 1;
	currword->spec_symb = 0;
	currword->join = 0;
	*i += 1;
	if (is_just_dollar(str, i, currword))
		return (1);
	currword->spec_symb = 2;
	currword->start = *i;
	currword->len = 0;
	while (str[*i] && isn_spec_symb(str, i))
	{
		*i += 1;
		currword->len += 1;
	}
	if (str[*i] == '\'' || str[*i] == '\"' || str[*i] == '$')
		currword->join = 1;
	return (1);
}

char	*find_env_var(char *str_to_find, t_list **env)
{
	t_list	*cur;
	char	*res;

	cur = *env;
	res = get_env_var(cur, str_to_find);
	return (res);
}
