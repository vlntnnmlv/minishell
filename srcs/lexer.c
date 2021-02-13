/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmalcom <qmalcom@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 23:36:07 by qmalcom           #+#    #+#             */
/*   Updated: 2020/12/07 00:49:34 by qmalcom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** here we have string after GNL
** creating draft list - to get rid of all unneeded stuff (slashes, etc.)
** then creating token list - pure tokens with marks of their type -
** special or regular
** return it to parser
*/

void	new_command(char *str, t_shell *shell)
{
	t_wlist	*draft_list;

	draft_list = create_draft_list(str, shell);
	if (!draft_list)
	{
		free(str);
		return ;
	}
	free(str);
	create_tokens_list(draft_list, shell);
	wlist_clean(draft_list);
	return ;
}
