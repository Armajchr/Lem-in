/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <armajchr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 15:15:42 by armajchr          #+#    #+#             */
/*   Updated: 2020/03/03 14:35:37 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_visu	init_src2_dst2(t_visu *visu)
{
	visu->src2.x = 0;
	visu->src2.y = 0;
	visu->src2.h = 50;
	visu->src2.w = 50;
	visu->dst2.x = visu->x;
	visu->dst2.y = visu->y;
	visu->dst2.h = 30;
	visu->dst2.w = 30;
	return (*visu);
}

void	render_part1(t_visu *visu, t_room *room)
{
	*visu = init_src2_dst2(visu);
	SDL_SetRenderDrawColor(visu->renderer, 0, 0, 0, 255);
	SDL_RenderClear(visu->renderer);
	SDL_RenderCopy(visu->renderer, visu->bmptexture, &visu->src, &visu->dst);
	if (visu->l + 1 < room->ants)
	{
		SDL_RenderCopy(visu->renderer, visu->bmptexture, &visu->src1,
			&visu->dst1);
		SDL_RenderCopy(visu->renderer, visu->bmptexture, &visu->src2,
			&visu->dst2);
	}
	else
		SDL_RenderCopy(visu->renderer, visu->bmptexture, &visu->src2,
			&visu->dst2);
	SDL_SetRenderDrawColor(visu->renderer, 0, 255, 0, 255);
	SDL_RenderCopy(visu->renderer, visu->texture, NULL, &visu->position);
	SDL_SetRenderDrawColor(visu->renderer, 255, 0, 0, 255);
	SDL_RenderDrawRects(visu->renderer, visu->rect, room->rooms_nb);
	SDL_SetRenderDrawColor(visu->renderer, 0, 255, 0, 255);
	SDL_RenderCopy(visu->renderer, visu->texture2, NULL, &visu->position2);
	if (visu->end != 1)
		visu->index++;
}

void	render_part3(t_visu *visu, t_room *room)
{
	if (visu->end != 1)
	{
		SDL_SetRenderDrawColor(visu->renderer, 200, 200, 200,
				100);
		SDL_RenderCopy(visu->renderer, visu->counter[visu->l],
				NULL, &visu->position3);
	}
	else
		visu->l++;
	if (visu->l == room->ants)
	{
		visu->check = 1;
		visu->l++;
	}
}

void	render_part2(t_visu *visu, t_room *room)
{
	visu->i = 0;
	while (visu->i < room->rooms_nb)
	{
		SDL_RenderCopy(visu->renderer, visu->names[visu->i],
				NULL, &visu->coords[visu->i]);
		visu->i++;
	}
	visu->k = 0;
	while (visu->k < room->links_nb * 3)
	{
		SDL_SetRenderDrawColor(visu->renderer, 200, 0, 200, 255);
		SDL_RenderDrawLine(visu->renderer,
				visu->points[visu->k].x, visu->points[visu->k].y,
				visu->points[visu->k + 1].x,
				visu->points[visu->k + 1].y);
		visu->k += 2;
	}
	if (visu->l < room->ants && visu->check == 0)
		render_part3(visu, room);
}

void	render_destroy(t_visu *visu)
{
	SDL_DestroyTexture(*visu->names);
	SDL_DestroyTexture(*visu->counter);
	SDL_DestroyTexture(visu->bmptexture);
	SDL_DestroyTexture(visu->texture);
	SDL_DestroyRenderer(visu->renderer);
	SDL_DestroyWindow(visu->screen);
	TTF_Quit();
	SDL_Quit();
}
