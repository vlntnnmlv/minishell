/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmalcom <qmalcom@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 18:10:34 by rmarguri          #+#    #+#             */
/*   Updated: 2020/12/07 00:54:30 by qmalcom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		f_new_pwd(t_clist *clist, t_shell *shell)
{
	char	*d;

	d = getcwd(NULL, 0);
	if (!d)
		d = get_env_var(shell->env, "PWD");
	if (d)
	{
		ft_putstr_fd(d, clist->fd_out_f);
		ft_putchar_fd('\n', clist->fd_out_f);
	}
	free(d);
	return (0);
}
