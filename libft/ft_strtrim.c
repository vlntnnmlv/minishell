/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarguri <rmarguri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 19:21:14 by rmarguri          #+#    #+#             */
/*   Updated: 2020/05/29 16:26:57 by rmarguri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	trimable(char c, char const *set)
{
	while (*set != '\0')
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	int		len;
	int		i;

	if (!s1)
		return (NULL);
	if (!set)
		return ((char*)s1);
	i = 0;
	len = ft_strlen(s1) - 1;
	while (trimable((char)s1[i], set))
		i++;
	while (trimable((char)s1[len], set) && len > i)
		len--;
	if (len < i)
		return (ft_strdup(""));
	return (ft_substr(s1, i, len - i + 1));
}
