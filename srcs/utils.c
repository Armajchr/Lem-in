/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <armajchr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 14:54:13 by armajchr          #+#    #+#             */
/*   Updated: 2020/01/17 14:23:21 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	rev_lst(t_nod *nod)
{
	t_nod	*previous;
	t_nod	*current;
	t_nod	*next;

	current = nod->first;
	previous = NULL;
	while (current)
	{
		next = current->next;
		current->next = previous;
		previous = current;
		current = next;
	}
	nod->first = previous;
}

void	rev_lst2(t_lst *list)
{
	t_lst	*previous;
	t_lst	*current;
	t_lst	*next;

	current = list->first;
	previous = NULL;
	while (current)
	{
		next = current->next;
		current->next = previous;
		previous = current;
		current = next;
	}
	list->first = previous;
}

t_lst	*ft_checked_last(t_lst *tmp, t_nod *thisistheway, t_lst *checked)
{
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = ft_create_elem2(checked);
	tmp->next->name = thisistheway->name;
	return (tmp);
}

void	ft_list_push_end(t_lst *checked, t_nod *thisistheway, t_lst *list)
{
	t_lst	*tmp;
	t_lst	*tmp2;
	int		i;

	tmp = checked->first;
	tmp2 = list->first;
	if (tmp)
	{
		tmp = ft_checked_last(tmp, thisistheway, checked);
		{
			i = 0;
			while (i < tmp2->k)
			{
				tmp->next->father[i] = tmp2->father[i];
				tmp->next->k++;
				i++;
			}
		}
	}
	else
	{
		checked->first = ft_create_elem2(checked);
		checked->first->name = thisistheway->name;
	}
}

t_lst	*ft_list_push_back(t_lst *list, t_nod *tmp, int i)
{
	t_lst	*tmp2;

	tmp2 = list->first;
	if (tmp2)
	{
		while (tmp2->next)
			tmp2 = tmp2->next;
		tmp2->next = ft_create_elem2(list);
		tmp2->next->name = tmp->links[i];
		tmp2->next->check = 0;
		tmp2->next->k = 0;
	}
	else
		list->first = ft_create_elem2(list);
	return (tmp2);
}
