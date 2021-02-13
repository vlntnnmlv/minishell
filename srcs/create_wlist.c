/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_wlist.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmalcom <qmalcom@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 23:33:36 by qmalcom           #+#    #+#             */
/*   Updated: 2020/12/08 16:29:06 by qmalcom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_wlist	*create_draft_list(char *str, t_shell *shell)
{
	int			i;
	t_currword	currword;
	t_wlist		*draft_list;
	t_wlist		*last;

	i = 0;
	draft_list = NULL;
	currword.ret_to_dq = 0;
	if (!str[i])
		return (NULL);
	while (str[i] && search_word(str, &i, &currword))
		draft_list = wslist_add(draft_list,
							new_word(str, &currword));
	last = wlistlast(draft_list);
	if (check_wlist(draft_list))
	{
		wlist_clean(draft_list);
		set_exit_status(258, shell);
		return (NULL);
	}
	return (draft_list);
}

t_wlist	*new_word(char *str, t_currword *currword)
{
	t_wlist	*new;

	if (!(new = malloc(sizeof(t_wlist))))
		exit(1);
	new->next = NULL;
	new->join_next = (currword ? currword->join : 0);
	new->spec_symb = currword->spec_symb;
	if (currword && !(new->word =
	ft_substr(str, currword->start, currword->len)))
		exit(1);
	if (!currword && !(new->word = ft_strdup("")))
		exit(1);
	return (new);
}

t_wlist	*wlistlast(t_wlist *words)
{
	while (words)
	{
		if (!(words->next))
			return (words);
		words = words->next;
	}
	return (NULL);
}

/*
** adding words to list, one by one without checking
*/

t_wlist	*wslist_add(t_wlist *first_elem, t_wlist *new_word)
{
	t_wlist *last;
	t_wlist *start;

	start = first_elem;
	if (!first_elem)
		return (new_word);
	last = wlistlast(start);
	last->next = new_word;
	return (start);
}

/*
** if ; or | is first token - error
** if token is redirection, and next is also some special token - error
** if token is redirection and it is the last word - newline error
** if command is only redirection or ; or | - error
** if couple of ; or | is together - error
*/

int		check_wlist(t_wlist *wlist)
{
	t_wlist	*temp;
	uint	tok;

	temp = wlist;
	if (temp && what_spec_symb(temp) > 4)
		return (synt_error(temp->word));
	while (temp)
	{
		tok = what_spec_symb(temp);
		if (tok > 0 && tok <= 4)
		{
			if (temp->next && what_spec_symb(temp->next) > 0)
				return (synt_error(temp->next->word));
		}
		if (tok > 4)
		{
			if (temp->next && what_spec_symb(temp->next) > 4)
				return (synt_error(temp->next->word));
		}
		if (tok > 0 && tok != TOK_NEXT && !temp->next)
			return (synt_error("newline"));
		temp = temp->next;
	}
	return (0);
}
