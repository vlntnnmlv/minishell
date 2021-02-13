/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmalcom <qmalcom@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 15:33:50 by rmarguri          #+#    #+#             */
/*   Updated: 2020/12/07 00:32:30 by qmalcom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


t_shell g_shell;

int		main(int ac, char **av, char **env)
{
	ac = 0;
	av = NULL;
	shell_init(&g_shell, env);
	shell_iter(&g_shell);
	return (0);
}
