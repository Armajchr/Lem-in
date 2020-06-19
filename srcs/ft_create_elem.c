/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_elem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <armajchr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 14:35:32 by armajchr          #+#    #+#             */
/*   Updated: 2020/06/17 14:19:24 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_nod	*ft_create_elem(t_nod *elem)
{
	if (!(elem = malloc(sizeof(t_nod))))
		return (NULL);
	if (elem)
	{
		elem->start = 0;
		elem->end = 0;
		elem->next = NULL;
	}
	return (elem);
}

t_lst	*ft_create_elem2(t_lst *elem2)
{
	if (!(elem2 = malloc(sizeof(t_lst))))
		return (NULL);
	if (elem2)
	{
		elem2->k = 0;
		elem2->next = NULL;
	}
	return (elem2);
}
