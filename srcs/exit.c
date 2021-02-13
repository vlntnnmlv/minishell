/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarguri <rmarguri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 19:45:09 by rmarguri          #+#    #+#             */
/*   Updated: 2020/12/08 17:15:39 by rmarguri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		is_bigger(char *s)
{
	if (s[0] != '-' && ft_strncmp(s, "9223372036854775807", 19) > 0)
		return (1);
	if (s[0] == '-' && ft_strncmp(s + 1, "9223372036854775808", 19) > 0)
		return (1);
	return (0);
}

int		ft_isdigits(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!ft_isdigit(s[i]) && s[i] != '-' && s[i] != '+')
			return (0);
		i++;
	}
	return (1);
}

int		f_new_exit(t_clist *clist, t_shell *shell)
{
	int	i;
	int	k;

	shell->status = 0;
	if (clist->args_count != 0)
	{
		i = 0;
		if ((k = ft_isdigits(clist->first_arg->token)) == 0 || \
		is_bigger(clist->first_arg->token))
		{
			shell->status = 255;
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(clist->first_arg->token, 2);
			ft_putstr_fd(": numeric argument reguired\n", 2);
			exit(shell->status);
		}
		if (clist->args_count == 1)
			shell->status = ft_atoi(clist->first_arg->token);
		else
		{
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			return (1);
		}
	}
	exit(shell->status);
}
