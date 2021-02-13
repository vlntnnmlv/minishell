/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarguri <rmarguri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 19:34:14 by rmarguri          #+#    #+#             */
/*   Updated: 2020/05/26 17:25:52 by rmarguri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t			ft_strlcat(char *dest, const char *src, size_t n)
{
	size_t i;
	size_t dlen;
	size_t slen;

	dlen = ft_strlen(dest);
	slen = ft_strlen(src);
	i = 0;
	if (n <= dlen)
		return (slen + n);
	while (src[i] && (i < n - dlen - 1))
	{
		dest[i + dlen] = src[i];
		i++;
	}
	dest[i + dlen] = '\0';
	return (dlen + slen);
}
