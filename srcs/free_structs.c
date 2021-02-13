/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmalcom <qmalcom@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 13:28:39 by qmalcom           #+#    #+#             */
/*   Updated: 2020/12/08 13:55:24 by qmalcom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_darr(char **darr)
{
	int i;

	i = -1;
	if (darr)
	{
		while (darr[++i])
		{
			free(darr[i]);
			darr[i] = NULL;
		}
		free(darr);
		darr = NULL;
	}
}

void	free_struct(t_parsed *parse_result)
{
	t_wlist *curr_word;
	t_wlist *next_word;

	if (parse_result)
	{
		curr_word = *(parse_result->wlist);
		while (curr_word)
		{
			if (curr_word->word)
				free(curr_word->word);
			next_word = curr_word->next;
			free(curr_word);
			curr_word = next_word;
		}
		free(parse_result);
		parse_result = NULL;
	}
}

void	wlist_clean(t_wlist *wlist)
{
	t_wlist *curr_word;
	t_wlist *next_word;

	curr_word = wlist;
	while (curr_word)
	{
		if (curr_word->word)
			free(curr_word->word);
		next_word = curr_word->next;
		free(curr_word);
		curr_word = next_word;
	}
}

void	tlist_clean(t_tlist *tlist)
{
	t_tlist *next_token;

	while (tlist)
	{
		if (tlist->token)
			free(tlist->token);
		next_token = tlist->next;
		free(tlist);
		tlist = next_token;
	}
}

void	free_clist(t_clist *clist)
{
	if (clist)
	{
		if (clist->cmd)
			free(clist->cmd);
		if (clist->in_file_name)
			free(clist->in_file_name);
		if (clist->out_file_name)
			free(clist->out_file_name);
		tlist_clean(clist->first_arg);
		free(clist);
	}
}
