/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarguri <rmarguri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 19:17:13 by rmarguri          #+#    #+#             */
/*   Updated: 2020/05/27 16:00:18 by rmarguri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t n, size_t m)
{
	void *str;

	if (!(str = (unsigned char*)malloc(m * n)))
		return (NULL);
	ft_bzero(str, m * n);
	return (str);
}
