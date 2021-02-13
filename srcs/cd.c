/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmalcom <qmalcom@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 18:05:53 by rmarguri          #+#    #+#             */
/*   Updated: 2020/12/08 16:38:32 by qmalcom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	cd_no_file_error(char *file)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	return (1);
}

void		set_pwd(t_shell *shell)
{
	char	*d;
	char	*tmp;
	char	*prev;

	if (!(prev = getcwd(NULL, 0)))
		prev = get_env_var(shell->env, "PWD");
	if (!(tmp = ft_strjoin("OLDPWD=", prev)))
		exit(1);
	d = get_env_var(shell->env, "HOME");
	if (d)
	{
		chdir(d);
		search_env_var(tmp, &shell->env);
		free(tmp);
		if (!(tmp = ft_strjoin("PWD=", getcwd(NULL, 0))))
			exit(1);
		search_env_var(tmp, &shell->env);
		free(tmp);
		free(d);
	}
	else
		free(tmp);
}

int			messed_up_dir(t_clist *clist, t_shell *shell)
{
	char *d;
	char *tmp;

	tmp = get_env_var(shell->env, "PWD");
	d = ft_strjoin(tmp, "/");
	free(tmp);
	tmp = ft_strjoin(d, clist->first_arg->token);
	set_env_var(shell->env, "PWD", tmp);
	free(tmp);
	ft_putstr_fd("cd: error retrieving current directory: \
getcwd: cannot access parent directories: \
No such file or directory\n", 2);
	return (1);
}

int			foo(char *d, t_clist *clist, t_shell *shell)
{
	char	*tmp;
	char	*prev;

	if (!(prev = getcwd(NULL, 0)))
		prev = get_env_var(shell->env, "PWD");
	if (!(tmp = ft_strjoin("OLDPWD=", prev)))
		exit(1);
	if (chdir(d) == -1)
		return (permission_error(d));
	d = getcwd(NULL, 0);
	if (d)
	{
		search_env_var(tmp, &shell->env);
		free(tmp);
		if (!(tmp = ft_strjoin("PWD=", d)))
			exit(1);
		search_env_var(tmp, &shell->env);
		free(tmp);
		return (0);
	}
	else
	{
		free(tmp);
		return (messed_up_dir(clist, shell));
	}
}

int			f_new_cd(t_clist *clist, t_shell *shell)
{
	char	*d;
	t_stat	b;

	if (clist->args_count == 0)
		set_pwd(shell);
	else if (clist->args_count >= 1)
	{
		if (!stat(clist->first_arg->token, &b) && S_ISDIR(b.st_mode))
		{
			d = ft_strdup(clist->first_arg->token);
			return (foo(d, clist, shell));
			free(d);
		}
		else
			return (cd_no_file_error(clist->first_arg->token));
	}
	return (0);
}
