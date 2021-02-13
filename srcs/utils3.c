/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarguri <rmarguri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 19:12:01 by rmarguri          #+#    #+#             */
/*   Updated: 2020/12/06 15:35:55 by rmarguri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_state	exist_check(char *path)
{
	t_stat	b;
	int		k;

	k = stat(path, &b);
	if (k != 0)
		return (NSF);
	if (S_ISREG(b.st_mode))
		return (REG);
	if (S_ISDIR(b.st_mode))
		return (DRC);
	return (NIF);
}

void	print_list(t_list **env)
{
	t_list *cur;

	cur = *env;
	while (cur)
	{
		ft_putstr_fd(cur->content, 1);
		ft_putchar_fd('\n', 1);
		cur = cur->next;
	}
}

void	skip_spaces(char *str, int *i_cur)
{
	while (str[*i_cur] && (str[*i_cur] == ' '))
		*i_cur += 1;
}

int		set_exit_status(int res, t_shell *shell)
{
	char	*res_str;
	char	*res_itoa;

	if (!(res_itoa = ft_itoa(res)))
		exit(1);
	if (!(res_str = ft_strjoin("?=", res_itoa)))
		exit(1);
	free(res_itoa);
	search_env_var(res_str, &shell->env);
	free(res_str);
	return (res);
}

int		show_prompt(t_shell shell)
{
	char	*tmp;

	tmp = get_env_var(shell.env, "PWD");
	ft_putstr_fd(BLU, 2);
	ft_putstr_fd(tmp, 2);
	free(tmp);
	ft_putstr_fd(ESC, 2);
	ft_putstr_fd(" ", 2);
	ft_putstr_fd(BMGT, 2);
	ft_putstr_fd(shell.prompt, 2);
	ft_putstr_fd(ESC, 2);
	return (0);
}
