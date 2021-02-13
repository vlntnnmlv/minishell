/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmalcom <qmalcom@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 17:53:10 by qmalcom           #+#    #+#             */
/*   Updated: 2020/12/08 13:48:18 by qmalcom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	init_cmds(int (*cmds[])(t_clist*, t_shell*))
{
	cmds[0] = &f_new_echo;
	cmds[1] = &f_new_cd;
	cmds[2] = &f_new_pwd;
	cmds[3] = &f_new_export;
	cmds[4] = &f_new_unset;
	cmds[5] = &f_new_env;
	cmds[6] = &f_new_exit;
}

static void	fill_builtin(t_shell *shell)
{
	int	i;

	i = -1;
	if (!(shell->prompt = ft_strdup("minishell$ ")))
		exit(1);
	if (!(shell->commands = (char**)malloc(7 * sizeof(char*))))
		exit(1);
	shell->commands[0] = ft_strdup("echo");
	shell->commands[1] = ft_strdup("cd");
	shell->commands[2] = ft_strdup("pwd");
	shell->commands[3] = ft_strdup("export");
	shell->commands[4] = ft_strdup("unset");
	shell->commands[5] = ft_strdup("env");
	shell->commands[6] = ft_strdup("exit");
	while (++i < 7)
	{
		if (!shell->commands[i])
			exit(1);
	}
}

int			shell_init(t_shell *shell, char **env)
{
	int		env_l;
	int		i;

	fill_builtin(shell);
	shell->env_std = NULL;
	env_l = 0;
	while (env[env_l])
		env_l++;
	shell->env = ft_lstnew(env[0], ft_strlen(env[0]) + 1);
	i = 1;
	while (env[i])
	{
		ft_lst_push_back(&shell->env, env[i], ft_strlen(env[i]) + 1);
		i += 1;
	}
	ft_lst_push_back(&shell->env, "?=0", 3);
	init_cmds(shell->cmds);
	return (0);
}
