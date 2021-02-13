/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarguri <rmarguri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 15:51:03 by rmarguri          #+#    #+#             */
/*   Updated: 2020/08/21 16:40:58 by rmarguri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_lstlast(t_list *list)
{
	t_list *cur;

	cur = list;
	while (cur->next)
		cur = cur->next;
	return (cur->content);
}
