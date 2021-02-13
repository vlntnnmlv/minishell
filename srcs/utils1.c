/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmalcom <qmalcom@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 18:28:09 by rmarguri          #+#    #+#             */
/*   Updated: 2020/12/06 20:23:33 by qmalcom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_env_var(t_list *env, char *name)
{
	t_list	*cur;
	char	*str;

	cur = env;
	str = NULL;
	while (cur)
	{
		if (!ft_strncmp(name, (char*)cur->content, ft_strlen(name)) \
		&& ((char*)cur->content)[ft_strlen(name)] == '=')
			return (ft_strdup(cur->content + ft_strlen(name) + 1));
		cur = cur->next;
	}
	if (!(str = ft_strdup("")))
		exit(1);
	return (str);
}

int		set_env_var(t_list *env, char *name, char *value)
{
	t_list	*cur;
	char	*tmp;
	char	*tmp2;

	cur = env;
	while (cur)
	{
		if (!ft_strncmp(name, (char*)cur->content, ft_strlen(name)) \
		&& ((char*)cur->content)[ft_strlen(name)] == '=')
		{
			free(cur->content);
			cur->content = ft_strjoin(name, "=");
			tmp = cur->content;
			free(cur->content);
			cur->content = ft_strjoin(tmp, value);
			return (0);
		}
		cur = cur->next;
	}
	tmp = ft_strjoin(name, "=");
	tmp2 = tmp;
	free(tmp);
	tmp = ft_strjoin(tmp2, value);
	ft_lst_push_back(&env, tmp, ft_strlen(tmp) + 1);
	return (0);
}

void	del_el(t_list *cur, t_list *prv)
{
	if (cur->next == NULL)
	{
		free(cur->content);
		free(cur);
		cur = NULL;
		prv->next = NULL;
	}
	else
	{
		prv->next = cur->next;
		free(cur->content);
		free(cur);
		cur = prv->next;
	}
}

int		del_env_var(t_list *env, char *name)
{
	t_list	*cur;
	t_list	*prv;

	cur = env;
	prv = NULL;
	while (cur)
	{
		if (!ft_strncmp(name, (char*)cur->content, ft_strlen(name)) \
		&& ((char*)cur->content)[ft_strlen(name)] == '=')
		{
			del_el(cur, prv);
			return (0);
		}
		prv = cur;
		cur = cur->next;
	}
	return (0);
}

int		isset(char *str, char *set)
{
	int i;

	if (!str)
		return (1);
	i = 0;
	while (str[i] != '\0')
	{
		if (!ft_strchr(set, str[i]))
			return (0);
		i++;
	}
	return (1);
}
