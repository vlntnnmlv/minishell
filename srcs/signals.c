/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarguri <rmarguri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 23:45:11 by qmalcom           #+#    #+#             */
/*   Updated: 2020/12/06 15:51:44 by rmarguri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern	t_shell g_shell;

void	handle_sigquit(int sign)
{
	signal(sign, SIG_IGN);
	if (g_shell.pid != 0)
	{
		kill(g_shell.pid, sign);
		ft_putstr_fd("Quit (code dumped)\n", 1);
		search_env_var("?=131", &g_shell.env);
	}
	else
		ft_putstr_fd("\b\b  \b\b", 1);
	signal(sign, handle_sigquit);
	g_shell.pid = 0;
}

void	handle_sigint(int sign)
{
	signal(sign, SIG_IGN);
	if (g_shell.pid != 0)
	{
		kill(g_shell.pid, sign);
		search_env_var("?=130", &g_shell.env);
		g_shell.pid = 0;
	}
	else
	{
		ft_putchar_fd('\n', 1);
		show_prompt(g_shell);
	}
	search_env_var("?=1", &g_shell.env);
	signal(sign, handle_sigint);
	g_shell.pid = 0;
}
