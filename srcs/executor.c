/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmalcom <qmalcom@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 18:23:53 by rmarguri          #+#    #+#             */
/*   Updated: 2020/12/08 11:18:19 by qmalcom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		validate_new(char *command, t_shell *shell)
{
	int		i;

	i = 0;
	while (i < 7)
	{
		if (ft_strcmp(command, shell->commands[i]))
			return (i);
		i++;
	}
	return (-1);
}

void	handle_fork(t_clist *cur_cmd, t_shell *shell)
{
	int stat;

	shell->pid = fork();
	if (shell->pid == 0)
	{
		exec_builtout(cur_cmd, shell);
		close_fds(cur_cmd);
	}
	else
	{
		wait(&stat);
		close_fds(cur_cmd);
		if (WIFEXITED(stat))
			set_exit_status(WEXITSTATUS(stat), shell);
	}
}

void	handle_builtin_fork(int cmd_id, t_clist *cur_cmd, t_shell *shell)
{
	int	stat;
	int	r;

	shell->pid = fork();
	if (shell->pid == 0)
	{
		r = shell->cmds[cmd_id](cur_cmd, shell);
		set_exit_status(r, shell);
		close_fds(cur_cmd);
		exit(0);
	}
	else
	{
		wait(&stat);
		close_fds(cur_cmd);
		if (WIFEXITED(stat))
			set_exit_status(WEXITSTATUS(stat), shell);
	}
}

int		execute_one(t_clist *cur_cmd, t_shell *shell)
{
	int	cmd_id;
	int	r;

	if (cur_cmd->fd_in_f == -1)
	{
		close_fds(cur_cmd);
		set_exit_status(1, shell);
		return (1);
	}
	if (!cur_cmd->cmd || cur_cmd->cmd[0] == '\0')
		return (close_fds(cur_cmd));
	cmd_id = validate_new(cur_cmd->cmd, shell);
	if (cmd_id != -1 && !cur_cmd->pipe_next)
	{
		r = shell->cmds[cmd_id](cur_cmd, shell);
		set_exit_status(r, shell);
		close_fds(cur_cmd);
	}
	else if (cmd_id != -1 && cur_cmd->pipe_next)
		handle_builtin_fork(cmd_id, cur_cmd, shell);
	else if (cmd_id == -1)
		handle_fork(cur_cmd, shell);
	shell->pid = 0;
	return (0);
}

t_clist	*executor(t_clist *cmds, t_shell *shell)
{
	t_clist	*next;

	next = cmds->next_com;
	execute_one(cmds, shell);
	free_clist(cmds);
	return (next);
}
