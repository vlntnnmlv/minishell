/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmalcom <qmalcom@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 00:19:23 by qmalcom           #+#    #+#             */
/*   Updated: 2020/12/07 00:19:40 by qmalcom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_wlist	*skip_fname_token(t_wlist *wlist)
{
	if (!wlist->join_next)
		return (wlist->next);
	while (wlist->join_next == 1)
		wlist = wlist->next;
	return (wlist);
}

t_wlist	*skip_curr_command(t_wlist *wlist)
{
	while (wlist)
	{
		if (wlist->spec_symb && (ft_strcmp(wlist->word, ";") ||
								ft_strcmp(wlist->word, "|")))
			return (wlist);
		wlist = wlist->next;
	}
	return (wlist);
}
