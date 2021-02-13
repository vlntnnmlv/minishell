/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarguri <rmarguri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 19:21:04 by rmarguri          #+#    #+#             */
/*   Updated: 2020/05/25 19:21:07 by rmarguri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *small, size_t n)
{
	unsigned int i;
	unsigned int j;

	i = 0;
	j = ft_strlen(small);
	if (!*small)
		return ((char*)big);
	if (big == small)
		return ((char*)big);
	while (big[i] != '\0' && i < n)
	{
		j = 0;
		if (big[i] == small[j])
		{
			while (big[i + j] == small[j] && small[j] != '\0' \
			&& i + j < n)
				j++;
			if (j == ft_strlen(small))
				return ((char*)(big + i));
		}
		i++;
	}
	return (0);
}
