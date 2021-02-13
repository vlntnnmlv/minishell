/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmalcom <qmalcom@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 19:45:25 by rmarguri          #+#    #+#             */
/*   Updated: 2020/12/08 16:58:03 by qmalcom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**list_to_char(t_list *env)
{
	char	**res;
	t_list	*cur;
	int		l;
	int		i;

	l = ft_lstlen(env);
	res = (char**)malloc(sizeof(char*) * (l + 1));
	cur = env;
	i = 0;
	while (cur)
	{
		res[i] = ft_strdup((char*)cur->content);
		cur = cur->next;
		i++;
	}
	res[l] = NULL;
	return (res);
}

void	free_char(char **env)
{
	int		i;

	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
	env = NULL;
}

int		check_arg(char *str)
{
	int	i;

	i = -1;
	if (str && str[0] == '=')
		return (1);
	while (str[++i])
	{
		if (!ft_isalpha(str[i]) && str[i] != '=' && str[i] != '_')
			return (1);
		else if (!ft_isalpha(str[i]) && str[i] == '=')
			break ;
	}
	if (ft_strnchr(str, '=') == 0)
		return (2);
	return (0);
}

int		search_env_var(char *new_envv, t_list **env)
{
	t_list	*cur;
	int		i;

	i = 0;
	cur = *env;
	while (cur)
	{
		while (new_envv[i] && ((char*)cur->content)[i] &&
		new_envv[i] == ((char*)cur->content)[i])
		{
			if (new_envv[i] == '=')
			{
				free(cur->content);
				if (!(cur->content = ft_strdup(new_envv)))
					exit(1);
				return (1);
			}
			i += 1;
		}
		i = 0;
		cur = cur->next;
	}
	return (0);
}

int		f_new_export(t_clist *clist, t_shell *shell)
{
	t_tlist	*av;
	int		check_res;

	av = clist->first_arg;
	if (clist->args_count == 0)
		f_new_env(clist, shell);
	while (clist->args_count-- > 0)
	{
		if ((check_res = check_arg(av->token) == 1))
			return (wrong_var_error(av->token));
		else if (!check_res)
		{
			if (!search_env_var(av->token, &shell->env))
			{
				if (ft_strchr(av->token, '='))
					ft_lst_push_back(&shell->env, av->token,
					ft_strlen(av->token) + 1);
			}
		}
		av = av->next;
	}
	return (0);
}
