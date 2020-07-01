/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <armajchr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 12:06:35 by armajchr          #+#    #+#             */
/*   Updated: 2020/06/30 16:03:08 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	parsing_name(t_room *room, t_nod *nod)
{
	t_nod	*tmp;

	tmp = nod->first;
	while (tmp)
	{
		if (tmp->name[0] == 'L' || tmp->name[0] == '#')
		{
			room->check = 2;
			return ;
		}
		tmp = tmp->next;
	}
}

void	parsing_name2(t_room *room, t_nod *nod)
{
	t_nod	*tmp;
	t_nod	*tmp2;

	tmp = nod->first;
	tmp2 = tmp->next;
	while (tmp->next)
	{
		while (tmp2)
		{
			if (ft_strcmp(tmp->name, tmp2->name) == 0)
			{
				room->check = 2;
				return ;
			}
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
		tmp2 = tmp->next;
	}
}

void	parsing_xy(t_room *room, t_nod *nod)
{
	t_nod	*tmp;
	t_nod	*tmp2;

	tmp = nod->first;
	tmp2 = tmp->next;
	while (tmp->next)
	{
		while (tmp2)
		{
			if ((tmp->x == tmp2->x) && (tmp->y == tmp2->y))
			{
				room->check = 2;
				return ;
			}
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
		tmp2 = tmp->next;
	}
}

void	parsing_links(t_room *room, t_nod *nod)
{
	t_nod	*tmp;

	tmp = nod->first;
	while (tmp)
	{
		if (tmp->j < 0)
		{
			room->check = 2;
			return ;
		}
		tmp = tmp->next;
	}
}

void	parsing_lem(t_room *room, t_nod *nod, char *line)
{
	free(line);
	if (room->check == 2)
		return ;
	parsing_name(room, nod);
	if (room->check == 2)
		return ;
	parsing_name2(room, nod);
	if (room->check == 2)
		return ;
	parsing_xy(room, nod);
	if (room->check == 2)
		return ;
	parsing_links(room, nod);
	if (room->check == 2)
		return ;
}
