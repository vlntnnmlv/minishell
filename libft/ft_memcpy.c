/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarguri <rmarguri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 19:18:36 by rmarguri          #+#    #+#             */
/*   Updated: 2020/05/25 19:18:37 by rmarguri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*cstr;
	unsigned char	*csrc;

	cstr = (unsigned char *)dest;
	csrc = (unsigned char *)src;
	if (dest == src)
		return (dest);
	while (n--)
		*cstr++ = *csrc++;
	return (dest);
}
