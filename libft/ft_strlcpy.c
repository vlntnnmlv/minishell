/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarguri <rmarguri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 19:20:47 by rmarguri          #+#    #+#             */
/*   Updated: 2020/05/26 17:25:53 by rmarguri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcpy(char *dest, const char *src, size_t n)
{
	unsigned int i;

	if (n == 0)
		return (ft_strlen(src));
	i = 0;
	while (n > 1 && *src)
	{
		*dest = *src;
		++dest;
		++src;
		--n;
		++i;
	}
	*dest = '\0';
	while (*dest || *src)
	{
		if (*src)
		{
			++src;
			++i;
		}
	}
	return (i);
}
