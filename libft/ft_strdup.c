/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarguri <rmarguri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 19:20:36 by rmarguri          #+#    #+#             */
/*   Updated: 2020/10/03 17:00:59 by rmarguri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*res;
	int		i;

	res = (char*)malloc((ft_strlen(s) + 1) * sizeof(char));
	if (res)
	{
		i = 0;
		while (s[i] != '\0')
		{
			res[i] = s[i];
			i++;
		}
		res[i] = '\0';
		return (res);
	}
	return (NULL);
}

char	*ft_strdup_override(const char *s, int l)
{
	char	*res;
	int		i;

	res = (char*)malloc((l + 1) * sizeof(char));
	if (res)
	{
		i = 0;
		while (s[i] != '\0')
		{
			res[i] = s[i];
			i++;
		}
		while (i < l)
		{
			res[i] = ' ';
			i++;
		}
		res[i] = '\0';
		return (res);
	}
	return (NULL);
}
