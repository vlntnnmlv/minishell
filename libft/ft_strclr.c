/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strclr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarguri <rmarguri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 15:28:55 by rmarguri          #+#    #+#             */
/*   Updated: 2020/10/30 15:29:04 by rmarguri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strclr(char **s)
{
	if (s && *s)
	{
		free(*s);
		*s = NULL;
	}
}
