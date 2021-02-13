/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarguri <rmarguri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 19:18:26 by rmarguri          #+#    #+#             */
/*   Updated: 2020/05/25 19:18:27 by rmarguri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char *ss;
	unsigned char sym;

	ss = (unsigned char *)s;
	sym = (unsigned char)c;
	if (s || n)
	{
		while (n--)
		{
			if (*ss == sym)
				return (ss);
			ss++;
		}
	}
	return (NULL);
}
