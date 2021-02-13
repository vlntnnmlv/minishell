/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmalcom <qmalcom@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 16:54:30 by rmarguri          #+#    #+#             */
/*   Updated: 2020/12/07 00:53:24 by qmalcom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	no_args_check(t_tlist *tlist, t_clist *clist)
{
	if (!tlist || !tlist->token)
	{
		write(clist->fd_out_f, "\n", 1);
		return (1);
	}
	return (0);
}

int			f_new_echo(t_clist *clist, t_shell *shell)
{
	int		f_n;
	t_tlist *cur;

	shell = NULL;
	cur = clist->first_arg;
	f_n = 0;
	if (no_args_check(cur, clist))
		return (0);
	while (cur && ft_strcmp(cur->token, "-n"))
	{
		f_n = 1;
		cur = cur->next;
		clist->args_count -= 1;
	}
	while (clist->args_count > 0)
	{
		ft_putstr_fd(cur->token, clist->fd_out_f);
		if (clist->args_count != 1)
			ft_putchar_fd(' ', clist->fd_out_f);
		cur = cur->next;
		clist->args_count -= 1;
	}
	if (!f_n)
		write(clist->fd_out_f, "\n", 1);
	return (0);
}
