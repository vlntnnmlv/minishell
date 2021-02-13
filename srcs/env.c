/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmalcom <qmalcom@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 18:21:18 by rmarguri          #+#    #+#             */
/*   Updated: 2020/12/08 14:03:13 by qmalcom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	envv_sorter(char **envvars)
{
	int		i;
	char	*buffer;

	i = 0;
	while (envvars[i])
	{
		if (!envvars[i + 1] || (envvars[i + 1] &&
				ft_strncmp(envvars[i], envvars[i + 1],
				ft_strlen(envvars[i])) <= 0))
			i += 1;
		else if (envvars[i + 1] &&
				ft_strncmp(envvars[i], envvars[i + 1],
				ft_strlen(envvars[i])) > 0)
		{
			buffer = envvars[i];
			envvars[i] = envvars[i + 1];
			envvars[i + 1] = buffer;
			i = 0;
			continue;
		}
	}
}

int		f_new_env(t_clist *clist, t_shell *shell)
{
	t_list	*cur;
	int		i;
	t_clist	*skip;

	i = 0;
	cur = shell->env;
	skip = clist;
	if (!shell->env_std)
		shell->env_std = list_to_char(shell->env);
	envv_sorter(shell->env_std);
	while (shell->env_std[i])
	{
		if (!ft_strncmp(shell->env_std[i], "?=", 2))
		{
			i += 1;
			continue;
		}
		ft_putstr_fd(shell->env_std[i], 1);
		ft_putstr_fd("\n", 1);
		i += 1;
	}
	free_darr(shell->env_std);
	shell->env_std = NULL;
	return (0);
}
