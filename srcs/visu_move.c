/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_move.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <armajchr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 12:27:13 by armajchr          #+#    #+#             */
/*   Updated: 2020/03/04 11:13:00 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_visu	load_move_end(t_visu *visu, t_nod *tmp, t_path *path, t_room *room)
{
	visu->x = tmp->x * 100;
	visu->y = tmp->y * 100;
	visu->index = 0;
	if (visu->actual >= path->k && visu->l <= room->ants)
		visu->actual = 0;
	else
		visu->actual++;
	visu->end = 1;
	visu->move = 1;
	return (*visu);
}

t_visu	load_move_mid(t_visu *visu, t_nod *tmp)
{
	visu->x = tmp->x * 100;
	visu->y = tmp->y * 100;
	visu->move = 1;
	return (*visu);
}

t_visu	load_move(t_visu *visu, t_nod *nod, t_path *path, t_room *room)
{
	char	**way;
	t_nod	*tmp;
	int		i;

	visu->end = 0;
	i = 0;
	path->len = 0;
	way = ft_strsplit(path->path[visu->actual], 32);
	while (way[i])
		i++;
	path->len = i;
	way[visu->index] = ft_strrev(way[visu->index]);
	tmp = nod->first;
	while (ft_strcmp(tmp->name, way[visu->index]) != 0)
		tmp = tmp->next;
	if (tmp->end == 1)
		*visu = load_move_end(visu, tmp, path, room);
	else
		*visu = load_move_mid(visu, tmp);
	if (visu->actual >= path->k && visu->l <= room->ants)
		visu->actual = 0;
	SDL_Delay(2000);
	return (*visu);
}
