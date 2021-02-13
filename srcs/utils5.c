/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmalcom <qmalcom@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 14:44:30 by qmalcom           #+#    #+#             */
/*   Updated: 2020/12/06 20:21:31 by qmalcom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] == s2[i])
			i += 1;
		else
			return (0);
	}
	if (!s1[i] && !s2[i])
		return (1);
	return (0);
}

void	print_clist(t_clist *clist)
{
	int		i;
	t_clist	*cur;

	i = -1;
	cur = clist;
	while (cur)
	{
		while (++i < cur->args_count)
			cur->first_arg = cur->first_arg->next;
		i = -1;
		cur = cur->next_com;
	}
}

char	*glue_strings(char *str, int temp0, t_list *env)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_substr(str, 0, temp0);
	tmp2 = get_env_var(env, tmp);
	free(tmp);
	tmp = ft_strjoin(tmp2, str + temp0);
	free(tmp2);
	return (tmp);
}

int		ft_strclen(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (i);
}

char	*find_env_forexport(char *str, t_list **env)
{
	t_list	*cur;
	char	*tmp;
	int		l;

	cur = *env;
	while (cur)
	{
		l = ft_strclen(cur->content, '=');
		if (!ft_strncmp(cur->content, str, l))
		{
			tmp = glue_strings(str, l, *env);
			if (str[l] != '_' && \
				!ft_isdigit(str[l]) && \
				!ft_isalpha(str[l]))
				return (tmp);
		}
		cur = cur->next;
	}
	return (ft_strdup(""));
}
