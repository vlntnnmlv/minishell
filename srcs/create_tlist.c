/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tlist.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmalcom <qmalcom@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 04:54:38 by qmalcom           #+#    #+#             */
/*   Updated: 2020/12/07 13:47:33 by qmalcom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_tlist	*create_token(char *str)
{
	t_tlist	*new_token;

	if (!(new_token = malloc(sizeof(t_tlist))))
		exit(1);
	if (!(new_token->token = ft_strdup(str)))
		exit(1);
	new_token->next = NULL;
	new_token->prev = NULL;
	return (new_token);
}

char	*get_token(t_wlist **draft_list, t_shell *shell)
{
	char	*cur_tok;
	char	*temp_str;

	cur_tok = NULL;
	if ((*draft_list)->spec_symb == 2)
		cur_tok = find_env_var((*draft_list)->word, &shell->env);
	else
	{
		if (!(cur_tok = ft_strdup((*draft_list)->word)))
			exit(1);
	}
	while ((*draft_list) && (*draft_list)->join_next && (*draft_list)->next)
	{
		(*draft_list) = (*draft_list)->next;
		if ((*draft_list)->spec_symb == 2)
		{
			temp_str = find_env_forexport((*draft_list)->word, &shell->env);
			cur_tok = sum_strings(cur_tok, temp_str);
			free(temp_str);
		}
		else
			cur_tok = sum_strings(cur_tok, (*draft_list)->word);
	}
	return (cur_tok);
}

void	create_tokens_list(t_wlist *draft_list, t_shell *shell)
{
	t_clist	*cur_comm;
	int		handle_res;

	cur_comm = NULL;
	while (draft_list)
	{
		if (!cur_comm)
			cur_comm = init_command();
		if (draft_list->spec_symb == 0 || draft_list->spec_symb == 2)
			handle_res = clist_reg_comm(&draft_list, cur_comm, shell);
		else if (what_spec_symb(draft_list) == TOK_INF)
			handle_res = handle_inf(&draft_list, cur_comm, shell);
		else if (what_spec_symb(draft_list) == TOK_OUTF)
			handle_res = handle_outf(&draft_list, cur_comm, shell);
		else if (what_spec_symb(draft_list) == TOK_AOUTF)
			handle_res = handle_aoutf(&draft_list, cur_comm, shell);
		else if (what_spec_symb(draft_list) == TOK_PIPE)
			handle_res = handle_pipe(&draft_list, &cur_comm, shell);
		if (!draft_list || what_spec_symb(draft_list) == TOK_NEXT)
			handle_res = handle_next(&draft_list, &cur_comm, shell);
		if (handle_res == 1)
			continue;
	}
	free_clist(find_head(cur_comm));
}

t_tlist	*tlist_add(t_tlist *first_elem, t_tlist *new_word)
{
	t_tlist *last;
	t_tlist *start;

	start = first_elem;
	if (!new_word)
		return (NULL);
	if (!first_elem)
		return (new_word);
	last = tlistlast(start);
	last->next = new_word;
	last->next->prev = last;
	return (start);
}

t_tlist	*tlistlast(t_tlist *tokens)
{
	while (tokens)
	{
		if (!(tokens->next))
			return (tokens);
		tokens = tokens->next;
	}
	return (NULL);
}
