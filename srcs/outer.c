/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmalcom <qmalcom@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 19:42:24 by rmarguri          #+#    #+#             */
/*   Updated: 2020/12/08 07:36:54 by qmalcom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		exec_direct(char *exec, t_shell *shell)
{
	t_state	k;

	k = exist_check(exec);
	if (k == NSF)
		exit(before_exit(1, exec, ": No such file or directory\n", shell));
	else if (k == DRC)
		exit(before_exit(126, exec, ": is a directory\n", shell));
	else
	{
		shell->env_std = list_to_char(shell->env);
		if (!is_executable(exec))
			exit(before_exit(1, exec, ": Permission denied\n", shell));
		if (execve(exec, shell->av, shell->env_std) == -1)
			exit(before_exit(1, exec, ": error while executing\n", shell));
	}
	return (0);
}

int		close_fds(t_clist *clist)
{
	if (clist->fd_out_f > 1)
		close(clist->fd_out_f);
	if (clist->fd_in_f > 0)
		close(clist->fd_in_f);
	return (0);
}

int		exec_local(t_clist *clist, t_shell *shell)
{
	if (ft_strchr(clist->cmd, '/'))
	{
		dup2(clist->fd_out_f, 1);
		dup2(clist->fd_in_f, 0);
		close_fds(clist);
		exec_direct(clist->cmd, shell);
		return (0);
	}
	else
		return (1);
}

int		path_search(t_clist *clist, t_shell *shell, int i)
{
	char	*tmp;
	char	*path;
	t_state	k;

	tmp = ft_strjoin(shell->paths[i], "/");
	path = ft_strjoin(tmp, clist->cmd);
	free(tmp);
	k = exist_check(path);
	if (k == REG)
	{
		dup2(clist->fd_out_f, 1);
		dup2(clist->fd_in_f, 0);
		close_fds(clist);
		if (execve(path, shell->av, shell->env_std) == -1)
		{
			free(path);
			exit(set_exit_status(1, shell));
		}
	}
	return (0);
}

int		exec_builtout(t_clist *clist, t_shell *shell)
{
	int		i;
	char	*tmp;

	shell->av = clist_to_char(clist);
	shell->env_std = list_to_char(shell->env);
	if (exec_local(clist, shell))
	{
		i = 0;
		tmp = get_env_var(shell->env, "PATH");
		shell->paths = ft_split(tmp, ':');
		free(tmp);
		while (shell->paths[i])
		{
			path_search(clist, shell, i);
			i++;
		}
		close_fds(clist);
		exit(before_exit(127, clist->cmd, ": command not found\n", shell));
	}
	return (0);
}
