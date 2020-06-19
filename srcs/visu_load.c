/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_load.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <armajchr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 11:57:11 by armajchr          #+#    #+#             */
/*   Updated: 2020/03/04 11:02:47 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_visu	fill_points(t_visu *visu, t_nod *tmp, t_nod *nod, t_nod *tmp2)
{
	while (visu->j < tmp->j)
	{
		tmp2 = nod->first;
		visu->points[visu->k].x = tmp->x * 100 + 15;
		visu->points[visu->k].y = tmp->y * 100 + 15;
		visu->k++;
		while (ft_strcmp(tmp->links[visu->j], tmp2->name) != 0)
			tmp2 = tmp2->next;
		visu->points[visu->k].x = tmp2->x * 100 + 15;
		visu->points[visu->k].y = tmp2->y * 100 + 15;
		visu->k++;
		visu->j++;
	}
	return (*visu);
}

t_visu	fill_rect(t_visu *visu, t_nod *tmp, t_room *room)
{
	if (visu->i < room->rooms_nb)
	{
		visu->rect[visu->i].x = tmp->x * 100;
		visu->rect[visu->i].y = tmp->y * 100;
		visu->rect[visu->i].w = 30;
		visu->rect[visu->i].h = 30;
	}
	return (*visu);
}

t_visu	load_items(t_visu *visu, t_nod *tmp, t_nod *nod, t_nod *tmp2)
{
	if (tmp->start == 1)
	{
		visu->pos_start.x = tmp->x * 100;
		visu->pos_start.y = tmp->y * 100;
	}
	else if (tmp->end == 1)
	{
		visu->pos_end.x = tmp->x * 100;
		visu->pos_end.y = tmp->y * 100;
	}
	tmp2 = nod->first;
	visu->rooms[visu->i] = TTF_RenderText_Blended(visu->font, tmp->name,
		visu->color2);
	if (!visu->rooms[visu->i])
		ft_printf("Error creating rooms[%d] : %s\n", visu->i,
			SDL_GetError());
	visu->names[visu->i] = SDL_CreateTextureFromSurface(visu->renderer,
		visu->rooms[visu->i]);
	if (!visu->names[visu->i])
		ft_printf("Error creating names[%d] : %s\n", visu->i,
			SDL_GetError());
	return (*visu);
}

t_visu	load_part2(t_visu *visu, t_nod *nod, t_room *room)
{
	t_nod	*tmp;
	t_nod	*tmp2;

	tmp = nod->first;
	while (tmp)
	{
		*visu = load_items(visu, tmp, nod, tmp2);
		visu->coords[visu->i].x = tmp->x * 100;
		visu->coords[visu->i].y = tmp->y * 100;
		SDL_QueryTexture(visu->names[visu->i], NULL, NULL,
			&visu->coords[visu->i].w, &visu->coords[visu->i].h);
		SDL_FreeSurface(visu->rooms[visu->i]);
		visu->j = 0;
		*visu = fill_points(visu, tmp, nod, tmp2);
		*visu = fill_rect(visu, tmp, room);
		visu->i++;
		tmp = tmp->next;
	}
	return (*visu);
}
