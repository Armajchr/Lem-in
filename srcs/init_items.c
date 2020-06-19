/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_items.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <armajchr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 12:23:12 by armajchr          #+#    #+#             */
/*   Updated: 2020/02/10 16:36:40 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_lst	init_list(t_lst *list)
{
	list->first = NULL;
	list->next = NULL;
	list->name = "\0";
	list->k = 0;
	list->check = 0;
	list->weight = 0;
	ft_memset(list->father, '\0', sizeof(list->father));
	return (*list);
}

t_path	init_path(t_path *path)
{
	path->len = 0;
	path->max = 0;
	path->k = 0;
	
	return (*path);
}

t_nod	init_stack(t_nod *nod)
{
	nod->name = NULL;
	nod->x = 0;
	nod->y = 0;
	nod->first = NULL;
	nod->next = NULL;
	nod->j = 0;
	nod->start = 0;
	nod->end = 0;
	nod->check = 0;
	ft_memset(nod->links, '\0', sizeof(nod->links));
	return (*nod);
}

void	print_info(t_nod *nod)
{
	t_nod	*tmp;
	int		i;

	tmp = nod->first;
	if (tmp == NULL)
	{
		ft_printf(RED"La liste est vide\n"EOC);
		return ;
	}
	while (tmp)
	{
		ft_printf(CYAN"name=%s|x=%d|y=%d|start=%d|end=%d\n"EOC
				, tmp->name, tmp->x, tmp->y, tmp->start, tmp->end);
		i = 0;
		while (i < tmp->j)
		{
			ft_printf(GREEN"tmp->links[%d]=%s\n"EOC
					, i, tmp->links[i]);
			i++;
		}
		tmp = tmp->next;
	}
}

void	print_checked(t_lst *checked)
{
	t_lst	*tmp2;
	int		i;

	tmp2 = checked->first;
	while (tmp2)
	{
		i = 0;
		ft_printf(YELLOW"room name is %s\n"EOC, tmp2->name);
		while (tmp2->father[i])
		{
			ft_printf(CYAN"father is %s\n"EOC, tmp2->father[i]);
			i++;
		}
		tmp2 = tmp2->next;
	}
}
