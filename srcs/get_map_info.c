/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <armajchr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 15:34:30 by armajchr          #+#    #+#             */
/*   Updated: 2020/07/01 12:21:03 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	check_room_startend(t_nod *tmp, t_room *room)
{
	if (room->f & (F_START))
	{
		tmp->start = 1;
		room->f &= ~(F_START);
	}
	else if (room->f & (F_END))
	{
		tmp->end = 1;
		room->f &= ~(F_END);
	}
}

int		get_name_xy(char *line, t_room *room, t_nod *nod)
{
	t_nod *tmp;

	if (!(tmp = ft_create_elem(nod)))
		return (0);
	tmp->next = nod->first;
	nod->first = tmp;
	room->tab = ft_strsplit(line, 32);
	free(line);
	if (room->tab[0] == NULL || room->tab[1] == NULL || room->tab[2] == NULL
			|| room->tab[3] != NULL)
	{
		room->check = 2;
		return (0);
	}
	room->rooms_nb++;
	tmp->name = room->tab[0];
	tmp->x = ft_atoi(room->tab[1]);
	tmp->y = ft_atoi(room->tab[2]);
	if (tmp->x < 0 || tmp->y < 0)
		room->check = 2;
	if ((tmp->x > 2147483647) || (tmp->y > 2147483647))
		room->check = 2;
	tmp->j = 0;
	room->rooms = 1;
	check_room_startend(tmp, room);
	return (1);
}

int		link_error(t_room *room, char *line)
{
	if (room->tab[0] == NULL || room->tab[1] == NULL || room->tab[2]
			|| ft_strchr(line, ' '))
	{
		room->check = 2;
		free(line);
		return (1);
	}
	return (0);
}

int		get_links1(t_room *room, char *line, t_nod *nod)
{
	t_nod *tmp;

	if (!(room->tab = ft_strsplit(line, '-')))
		return (0);
	tmp = nod->first;
	if (link_error(room, line))
		return (0);
	free(line);
	while (room->tab && tmp->name && ft_strcmp(room->tab[0], tmp->name))
	{
		tmp = tmp->next;
		if (tmp == NULL)
		{
			room->check = 2;
			return (0);
		}
	}
	room->links_nb++;
	tmp->links[tmp->j] = room->tab[1];
	tmp->j++;
	return (1);
}

int		get_links2(t_room *room, t_nod *nod)
{
	t_nod *tmp;

	tmp = nod->first;
	if (room->tab[0] == NULL || room->tab[1] == NULL || room->tab[2])
	{
		room->check = 2;
		return (0);
	}
	while (ft_strcmp(room->tab[1], tmp->name) != 0)
	{
		tmp = tmp->next;
		if (tmp == NULL)
		{
			room->check = 2;
			return (0);
		}
	}
	tmp->links[tmp->j] = room->tab[0];
	tmp->j++;
	free(room->tab);
	room->links = 1;
	return (1);
}
