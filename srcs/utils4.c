/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarguri <rmarguri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 04:47:01 by qmalcom           #+#    #+#             */
/*   Updated: 2020/12/04 15:46:06 by rmarguri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*sum_strings(char *str1, char *str2)
{
	char	*str1_new;

	if (!(str1_new = ft_strjoin(str1, str2)))
		exit(1);
	free(str1);
	return (str1_new);
}

int		get_var_pos(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=' && str[i + 1])
			return (i);
		i += 1;
	}
	return (-1);
}

int		is_executable(char *exec)
{
	t_stat b;

	stat(exec, &b);
	if (S_IXUSR & b.st_mode)
		return (1);
	return (0);
}

char	**clist_to_char(t_clist *cmd)
{
	int		i;
	char	**res;
	t_tlist	*cur;

	i = 1;
	cur = cmd->first_arg;
	res = (char**)malloc(sizeof(char*) * (cmd->args_count + 2));
	res[0] = ft_strdup(cmd->cmd);
	while (i < cmd->args_count + 1)
	{
		res[i] = ft_strdup(cur->token);
		cur = cur->next;
		i++;
	}
	res[i] = NULL;
	i = 0;
	while (res[i])
		i++;
	return (res);
}

int		before_exit(int err, char *fun_name, char *mess, t_shell *shell)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(fun_name, 2);
	ft_putstr_fd(mess, 2);
	set_exit_status(err, shell);
	return (err);
}
