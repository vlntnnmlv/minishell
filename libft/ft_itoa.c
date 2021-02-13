/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarguri <rmarguri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 19:18:14 by rmarguri          #+#    #+#             */
/*   Updated: 2020/10/30 15:30:53 by rmarguri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_len(int n)
{
	size_t	len;

	len = 0;
	if (n < 0)
		len++;
	while (n > 9 || n < -9)
	{
		n = n / 10;
		len++;
	}
	len++;
	return (len);
}

static int		ft_num(int n)
{
	int	num;

	num = 0;
	if (n < 0)
		num = n % 10 * -1 + 48;
	else
		num = n % 10 + 48;
	return (num);
}

char			*ft_itoa(int n)
{
	size_t	tmp;
	char	*str;

	tmp = ft_len(n) - 1;
	if (!(str = ft_strnew(tmp + 1)))
		return (NULL);
	while (n > 9 || n < -9)
	{
		str[tmp--] = ft_num(n);
		n = n / 10;
	}
	str[tmp] = ft_num(n);
	if (n < 0)
		str[tmp - 1] = '-';
	return (str);
}
