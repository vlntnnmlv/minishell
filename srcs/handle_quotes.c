/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmalcom <qmalcom@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 20:11:29 by qmalcom           #+#    #+#             */
/*   Updated: 2020/12/08 10:44:18 by qmalcom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	word_btw_qoute(char *str, int *i, t_currword *currword)
{
	char quote;

	quote = str[(*i)++];
	currword->start = *i;
	currword->len = 0;
	currword->join = 0;
	currword->spec_symb = 0;
	while (str[*i] && str[*i] != quote)
		*i += 1;
	if (str[*i] == quote)
	{
		currword->len = *i - currword->start;
		currword->join = (str[*i + 1] && str[*i + 1] != ' ' ? 1 : 0);
	}
	*i += 1;
}

int		is_just_dq(char *str, int *i, t_currword *currword)
{
	if (str[*i] == '"')
	{
		currword->start = *i;
		currword->len = 0;
		currword->join = (str[*i + 1] && str[*i + 1] != ' ' ? 1 : 0);
		*i += 1;
		currword->spec_symb = 0;
		currword->ret_to_dq = 0;
		return (1);
	}
	return (0);
}

void	word_btw_dquote(char *str, int *i, t_currword *currword)
{
	*i += (str[*i] == '\"' ? 1 : 0);
	currword->start = *i;
	currword->len = 0;
	currword->join = 0;
	currword->spec_symb = 0;
	if (is_just_dq(str, i, currword))
		return ;
	if (is_env_var(str, i, currword))
		return ;
	if (is_only_dollar(str, i, currword))
		return ;
	if (is_reg_symb(str, i, currword))
		return ;
	if (is_bslash(str, i, currword))
		return ;
}
