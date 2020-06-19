/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_launch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <armajchr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 11:41:18 by armajchr          #+#    #+#             */
/*   Updated: 2020/06/18 13:49:12 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_visu	init_visu3(t_visu *visu)
{
	visu->pos_small.x = 450;
	visu->pos_small.y = 450;
	visu->position.x = 665;
	visu->position.y = 450;
	visu->i = 0;
	visu->j = 0;
	visu->k = 0;
	visu->l = 0;
	visu->dark_rect.x = 300;
	visu->dark_rect.y = 800;
	visu->dark_rect.w = 30;
	visu->dark_rect.h = 30;
	visu->src.x = 0;
	visu->src.y = 0;
	visu->src.h = 0;
	visu->src.w = 0;
	visu->dst.x = 650;
	visu->dst.y = 0;
	visu->dst.h = 900;
	visu->dst.w = 250;
	return (*visu);
}

t_visu	init_visu2(t_visu *visu, t_room *room, t_path *path)
{
	int	i;

	*visu = init_visu3(visu);
	visu->count = room->ants;
	visu->check = 0;
	visu->pos_start.x = 0;
	visu->pos_start.y = 0;
	visu->pos_end.x = 0;
	visu->pos_end.y = 0;
	visu->move = 0;
	visu->x = 0;
	visu->y = 0;
	visu->index = 0;
	visu->end = 0;
	visu->actual = 0;
	i = 0;
	while (i < path->k)
	{
		path->path[i] = ft_strrev(path->path[i]);
		i++;
	}
	return (*visu);
}

t_visu	init_visu(t_visu *visu, t_room *room, t_path *path)
{
	visu->isquit = 0;
	visu->bmp = SDL_LoadBMP("./Visu/lemin2ant.bmp");
	if (!visu->bmp)
		ft_printf("Error creating bmp : %s\n", SDL_GetError());
	visu->font = TTF_OpenFont("./Visu/THANK YOU KOBE.ttf", 28);
	if (!visu->font)
		ft_printf("Error creating font : %s\n", SDL_GetError());
	visu->text = TTF_RenderText_Blended(visu->font, "Lem-In", visu->color);
	if (!visu->text)
		ft_printf("Error creating text : %s\n", SDL_GetError());
	visu->texture = SDL_CreateTextureFromSurface(visu->renderer,
			visu->text);
	if (!visu->texture)
		ft_printf("Error creating texture : %s\n", SDL_GetError());
	visu->bmptexture = SDL_CreateTextureFromSurface(visu->renderer,
			visu->bmp);
	if (!visu->bmptexture)
		ft_printf("Error creating bmptexture : %s\n", SDL_GetError());
	visu->color = (SDL_Color) {0, 0, 0, 255};
	visu->color2 = (SDL_Color){0, 255, 0, 255};
	*visu = init_visu2(visu, room, path);
	return (*visu);
}

t_visu	load_part1(t_visu *visu)
{
	visu->text2 = TTF_RenderText_Blended(visu->font,
			"Number of ants left : ", visu->color2);
	if (!visu->text2)
		ft_printf("Error creating text : %s\n", SDL_GetError());
	visu->texture2 = SDL_CreateTextureFromSurface(visu->renderer,
			visu->text2);
	if (!visu->texture2)
		ft_printf("Error creating texture : %s\n", SDL_GetError());
	visu->position2.x = 30;
	visu->position2.y = 800;
	return (*visu);
}

t_visu	nb_ants_screen(t_visu *visu, t_room *room)
{
	visu->position3.x = 300;
	visu->position3.y = 800;
	while (visu->count > 0)
	{
		visu->text3[visu->l] = TTF_RenderText_Blended(visu->font,
				ft_itoa(visu->count), visu->color2);
		if (!visu->text3[visu->l])
			ft_printf("Error creating text : %s\n", SDL_GetError());
		visu->counter[visu->l] =
			SDL_CreateTextureFromSurface(visu->renderer,
					visu->text3[visu->l]);
		if (!visu->counter[visu->l])
			ft_printf("Error creating texture : %s\n",
					SDL_GetError());
		SDL_QueryTexture(visu->counter[visu->l], NULL, NULL,
				&visu->position3.w, &visu->position3.h);
		SDL_FreeSurface(visu->text3[visu->l]);
		visu->count--;
		visu->l++;
	}
	visu->l = 0;
	TTF_CloseFont(visu->font);
	return (*visu);
}
