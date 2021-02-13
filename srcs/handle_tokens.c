/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmalcom <qmalcom@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 19:06:04 by rmarguri          #+#    #+#             */
/*   Updated: 2020/12/08 07:08:42 by qmalcom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** handle infile redirection <
** if there is no token after "<" then stop, write error
** if there is special token after "<" (< > >> | ;) - write error
*/

int		handle_inf(t_wlist **wlist, t_clist *clist, t_shell *shell)
{
	char	*filename;

	*wlist = (*wlist)->next;
	filename = get_token(wlist, shell);
	if (clist->fd_in_f > 1)
	{
		close(clist->fd_in_f);
		free(clist->in_file_name);
	}
	clist->fd_in_f = open(filename, O_RDONLY);
	if (clist->fd_in_f == -1)
	{
		*wlist = skip_curr_command(*wlist);
		permission_re_wr(filename);
		free(filename);
		return (1);
	}
	clist->in_file_name = ft_strdup(filename);
	free(filename);
	*wlist = skip_fname_token(*wlist);
	return (0);
}

/*
** handle outfile redirection >
*/

int		handle_outf(t_wlist **wlist, t_clist *clist, t_shell *shell)
{
	char	*filename;

	*wlist = (*wlist)->next;
	filename = get_token(wlist, shell);
	if (clist->fd_out_f > 1)
	{
		close(clist->fd_out_f);
		free(clist->out_file_name);
	}
	clist->fd_out_f = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (clist->fd_out_f == -1)
	{
		*wlist = skip_curr_command(*wlist);
		permission_re_wr(filename);
		free(filename);
		return (1);
	}
	clist->out_file_name = ft_strdup(filename);
	free(filename);
	*wlist = skip_fname_token(*wlist);
	return (0);
}

/*
** handle outfile redirection with adding if file exists >>
*/

int		handle_aoutf(t_wlist **wlist, t_clist *clist, t_shell *shell)
{
	char	*filename;

	*wlist = (*wlist)->next;
	filename = get_token(wlist, shell);
	if (clist->fd_out_f > 1)
	{
		close(clist->fd_out_f);
		free(clist->out_file_name);
	}
	clist->fd_out_f = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (clist->fd_out_f == -1)
	{
		*wlist = skip_curr_command(*wlist);
		permission_re_wr(filename);
		free(filename);
		return (1);
	}
	clist->out_file_name = ft_strdup(filename);
	free(filename);
	*wlist = skip_fname_token(*wlist);
	return (0);
}

/*
** handle pipe |
*/

int		handle_pipe(t_wlist **wlist, t_clist **clist, t_shell *shell)
{
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		exit(1);
	(*clist)->pipe_next = 1;
	if (!(*clist)->out_file_name)
		(*clist)->fd_out_f = pipe_fd[1];
	else
		close(pipe_fd[1]);
	(*clist)->next_com = init_command();
	(*clist)->next_com->prev_com = (*clist);
	(*clist)->next_com->fd_in_f = pipe_fd[0];
	(*clist)->next_com->pipe_next = 1;
	*clist = executor(*clist, shell);
	(*wlist) = (*wlist)->next;
	return (0);
}

/*
** handle end of command ;
*/

int		handle_next(t_wlist **wlist, t_clist **cur_comm, t_shell *shell)
{
	*cur_comm = executor(*cur_comm, shell);
	if (*wlist)
		(*wlist) = (*wlist)->next;
	if (!(*cur_comm))
		*cur_comm = init_command();
	return (0);
}
