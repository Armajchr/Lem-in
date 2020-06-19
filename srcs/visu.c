/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <armajchr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 11:50:53 by armajchr          #+#    #+#             */
/*   Updated: 2020/06/18 15:08:08 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	init_window(t_visu *visu, t_room *room, t_nod *nod, t_path *path)
{
	visu->screen = NULL;
	visu->renderer = NULL;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		ft_printf("Error SDL Init\n");
	if (TTF_Init() < 0)
		ft_printf("Error TTF Init\n");
	SDL_CreateWindowAndRenderer(900, 900,
			SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE, &visu->screen,
			&visu->renderer);
	*visu = init_visu(visu, room, path);
	*visu = load_part1(visu);
	*visu = load_part2(visu, nod, room);
	load_texture(visu);
}

void	load_texture(t_visu *visu)
{
	SDL_QueryTexture(visu->texture, NULL, NULL, &visu->position.w,
			&visu->position.h);
	SDL_FreeSurface(visu->bmp);
	SDL_FreeSurface(visu->text);
	SDL_QueryTexture(visu->texture2, NULL, NULL, &visu->position2.w,
			&visu->position2.h);
	SDL_SetRenderDrawBlendMode(visu->renderer, SDL_BLENDMODE_BLEND);
}

void	visu_exec(t_visu *visu, t_nod *nod, t_path *path, t_room *room)
{
	if (SDL_PollEvent(&visu->event))
	{
		if (visu->event.type == SDL_QUIT)
			visu->isquit = 1;
	}
	if (visu->l < room->ants)
	{
		if (visu->index <= path->len)
			*visu = load_move(visu, nod, path, room);
	}
}

t_visu	init_src1_dst1(t_visu *visu)
{
	visu->src1.x = 0;
	visu->src1.y = 0;
	visu->src1.h = 50;
	visu->src1.w = 50;
	visu->dst1.x = visu->pos_start.x;
	visu->dst1.y = visu->pos_start.y;
	visu->dst1.h = 30;
	visu->dst1.w = 30;
	return (*visu);
}

int		visu(t_nod *nod, t_path *path, t_room *room)
{
	t_visu		visu;
	
	if (room->rooms_nb > 30)
	{
		ft_printf(GREEN"le bar est plein\n"EOC);
		return (0);
	}
	init_window(&visu, room, nod, path);
	visu = init_src1_dst1(&visu);
	SDL_QueryTexture(visu.bmptexture, NULL, NULL, &visu.src.w, &visu.src.h);
	visu = nb_ants_screen(&visu, room);
	while (visu.isquit == 0)
	{
		visu_exec(&visu, nod, path, room);
		render_part1(&visu, room);
		render_part2(&visu, room);
		SDL_RenderPresent(visu.renderer);
	}
	render_destroy(&visu);
	return (0);
}
