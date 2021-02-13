/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmalcom <qmalcom@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 16:22:50 by qmalcom           #+#    #+#             */
/*   Updated: 2020/12/07 13:48:16 by qmalcom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_clist	*init_command(void)
{
	t_clist	*new_comm;

	if (!(new_comm = malloc(sizeof(t_clist))))
		exit(1);
	new_comm->cmd = NULL;
	new_comm->fd_in_f = 0;
	new_comm->in_file_name = NULL;
	new_comm->out_file_name = NULL;
	new_comm->fd_out_f = 1;
	new_comm->first_arg = NULL;
	new_comm->args_count = 0;
	new_comm->next_com = NULL;
	new_comm->prev_com = NULL;
	new_comm->pipe_next = 0;
	return (new_comm);
}

/*
** modify regular command
** add command name
** add pointer to first arg if exists
** add count of args
*/

int		clist_reg_comm(t_wlist **wlist, t_clist *clist, t_shell *shell)
{
	char	*cur_tok;

	cur_tok = get_token(wlist, shell);
	if (!clist->cmd)
		clist->cmd = ft_strdup(cur_tok);
	else
	{
		if (!clist->first_arg)
			clist->first_arg = create_token(cur_tok);
		else
			clist->first_arg = tlist_add(clist->first_arg,
							create_token(cur_tok));
		clist->args_count += 1;
	}
	if (cur_tok)
		free(cur_tok);
	*wlist = (*wlist)->next;
	return (0);
}

int		what_spec_symb(t_wlist *wlist)
{
	if (wlist->spec_symb == 1)
	{
		if (ft_strcmp(wlist->word, ">>"))
			return (TOK_AOUTF);
		if (ft_strcmp(wlist->word, ">"))
			return (TOK_OUTF);
		if (ft_strcmp(wlist->word, "<"))
			return (TOK_INF);
		if (ft_strcmp(wlist->word, "|"))
			return (TOK_PIPE);
		if (ft_strcmp(wlist->word, ";"))
			return (TOK_NEXT);
	}
	return (0);
}

/*
** we hade a tail of clist
** this func returns head of clist
*/

t_clist	*find_head(t_clist *clist)
{
	if (clist)
	{
		while (clist->prev_com)
			clist = clist->prev_com;
		return (clist);
	}
	return (NULL);
}
