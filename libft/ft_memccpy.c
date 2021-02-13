/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarguri <rmarguri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 19:18:20 by rmarguri          #+#    #+#             */
/*   Updated: 2020/05/29 16:29:18 by rmarguri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, void *src, int c, size_t n)
{
	unsigned char	*cstr;
	unsigned char	*csrc;
	unsigned char	sym;
	size_t			i;

	cstr = (unsigned char *)dest;
	csrc = (unsigned char *)src;
	sym = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		cstr[i] = csrc[i];
		if (cstr[i] == sym)
			return (dest + i + 1);
		i++;
	}
	return (NULL);
}
