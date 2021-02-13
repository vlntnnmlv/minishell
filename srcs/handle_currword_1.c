/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_currword_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmalcom <qmalcom@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 05:01:11 by qmalcom           #+#    #+#             */
/*   Updated: 2020/12/08 10:49:46 by qmalcom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		hndl_spec_symb(char *str, int *i, t_currword *currword)
{
	if (str[*i] == '\\' && ft_strncmp(&str[*i], "\\ ", 2) && str[*i + 1])
	{
		currword->start = ++(*i);
		*i += 1;
	}
	else if (str[*i] == '\\')
		currword->start = (*i)++;
	else if (!ft_strncmp(&str[*i], ">>", 2))
		return (fill_spec_symb(currword, i, 2));
	else if (str[*i] == '<' || str[*i] == '>' ||
	str[*i] == '|' || str[*i] == ';')
		return (fill_spec_symb(currword, i, 1));
	else if (str[*i] == '$')
		return (get_envvar_name(str, i, currword));
	else
		currword->start = *i;
	return (0);
}

int		isn_spec_symb(char *str, int *i)
{
	if (str[*i] != '\\' && str[*i] != ' ' && \
	str[*i] != '\'' && str[*i] != '\"' &&
	str[*i] != '<' && str[*i] != '>' && str[*i] != '|' &&
	str[*i] != ';' && str[*i] != '$')
		return (1);
	return (0);
}

void	is_join_next(char *str, int *i, t_currword *currword)
{
	if (str[*i] && str[*i] != ' ' && str[*i] != '|' &&
	str[*i] != '>' && str[*i] != '<' && str[*i] != ';')
		currword->join = 1;
	else
		currword->join = 0;
}

void	reg_word(char *str, int *i, t_currword *currword)
{
	currword->len = 0;
	currword->join = 0;
	if (hndl_spec_symb(str, i, currword))
		return ;
	while (str[*i] && isn_spec_symb(str, i))
		*i += 1;
	is_join_next(str, i, currword);
	currword->spec_symb = 0;
	currword->len = *i - currword->start;
}

int		search_word(char *str, int *i, t_currword *currword)
{
	if (!currword->ret_to_dq)
		skip_spaces(str, i);
	if (currword->ret_to_dq || (str[*i] && str[*i] == '\"'))
		word_btw_dquote(str, i, currword);
	else if (str[*i] && str[*i] == '\'')
		word_btw_qoute(str, i, currword);
	else if (str[*i])
		reg_word(str, i, currword);
	else
		return (0);
	return (1);
}
