/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarguri <rmarguri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 19:19:36 by rmarguri          #+#    #+#             */
/*   Updated: 2020/05/25 19:19:37 by rmarguri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	size_t len;

	len = ft_strlen(str) + 1;
	while (len--)
	{
		if (*str++ == c)
			return ((char *)(str - 1));
	}
	return (NULL);
}
