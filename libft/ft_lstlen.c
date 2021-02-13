/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarguri <rmarguri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 17:26:20 by rmarguri          #+#    #+#             */
/*   Updated: 2020/08/21 16:54:43 by rmarguri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_lstlen(t_list *list)
{
	int		i;
	t_list	*cur;

	i = 0;
	cur = list;
	while (cur->next != NULL)
	{
		cur = cur->next;
		i++;
	}
	return (i + 1);
}
