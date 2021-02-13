/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmalcom <qmalcom@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 19:45:44 by rmarguri          #+#    #+#             */
/*   Updated: 2020/12/07 00:56:39 by qmalcom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		f_new_unset(t_clist *clist, t_shell *shell)
{
	t_tlist	*av;
	int		i;

	av = clist->first_arg;
	i = 1;
	while (av)
	{
		del_env_var(shell->env, av->token);
		av = av->next;
	}
	return (0);
}
