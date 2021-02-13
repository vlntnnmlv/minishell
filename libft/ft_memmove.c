/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarguri <rmarguri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 19:18:53 by rmarguri          #+#    #+#             */
/*   Updated: 2020/05/25 19:18:55 by rmarguri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char *cstr;
	unsigned char *csrc;

	cstr = (unsigned char *)dest;
	csrc = (unsigned char *)src;
	if (csrc < cstr)
		while (n--)
			*(cstr + n) = *(csrc + n);
	else if (csrc > cstr)
		ft_memcpy(dest, src, n);
	return (dest);
}
