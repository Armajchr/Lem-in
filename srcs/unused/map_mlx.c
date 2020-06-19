/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_mlx.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <armajchr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 11:52:54 by armajchr          #+#    #+#             */
/*   Updated: 2019/11/27 13:57:54 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void    draw_line(int xi, int yi, int xf, int yf, void *mlx_ptr, void *win_ptr)
{
int dx;
int dy;
int i;
int xinc;
int yinc;
int cumul;
int x;
int y;

i = 1;
x = xi ;
y = yi ;
dx = xf - xi ;
dy = yf - yi ;
xinc = ( dx > 0 ) ? 1 : -1 ;
yinc = ( dy > 0 ) ? 1 : -1 ;
dx = (dx < 0) ? -dx : dx;
dy = (dy < 0) ? -dy : dy;
mlx_pixel_put(mlx_ptr, win_ptr, x, y, 11166975);
if ( dx > dy )
{
    cumul = dx / 2 ;
    while (i <= dx) 
    {
        x += xinc ;
        cumul += dy ;
        if ( cumul >= dx )
        {
            cumul -= dx ;
            y += yinc ;
        }
        mlx_pixel_put(mlx_ptr, win_ptr, x, y, 11166975);
        i++;
    }
}
    else
    {
        cumul = dy / 2 ;
        while (i <= dy) 
        {
            y += yinc ;
            cumul += dx ;
            if ( cumul >= dy )
            {
                cumul -= dy ;
                x += xinc ;
            }
            mlx_pixel_put(mlx_ptr, win_ptr, x, y, 11166975);
            i++;
    }

    }
}

void    visu(t_nod *nod)
{
    void    *mlx_ptr;
    void    *win_ptr;
    t_nod   *tmp;
    t_nod   *tmp2;
    int     i;

    mlx_ptr = mlx_init();
    win_ptr = mlx_new_window(mlx_ptr, 2500, 2000, "Lem_in");
    tmp = nod->first;
    while (tmp)
    {
        mlx_string_put(mlx_ptr, win_ptr, tmp->x * 20 - 7, tmp->y * 20, 16745060, "[");
        mlx_string_put(mlx_ptr, win_ptr, tmp->x * 20, tmp->y * 20, 16745060, tmp->name);
        mlx_string_put(mlx_ptr, win_ptr, tmp->x * 20 + 30, tmp->y * 20, 16745060, "]");
        tmp = tmp->next;
    }
    tmp = nod->first;
    while (tmp)
    {
        i = 0;
        tmp2 = nod->first;
        while (tmp->links[i])
        {
            while (ft_strcmp(tmp2->name, tmp->links[i]) != 0)
                tmp2 = tmp2->next;
            draw_line(tmp2->x * 20, tmp2->y * 20, tmp->x * 20, tmp->y * 20, mlx_ptr, win_ptr);
            i++;
            tmp2 = nod->first;
        }
        tmp = tmp->next;
    }
    mlx_loop(mlx_ptr);
}