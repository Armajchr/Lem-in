/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fast_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <armajchr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 14:01:03 by armajchr          #+#    #+#             */
/*   Updated: 2020/02/03 17:26:32 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void    fast_path(t_nod *nod, t_lst *checked, t_path *path2)
{
    t_lst   *tmp;
    t_nod   *tmp2;
    int     i;

    ft_printf("hello\n");
    clear_checked_rooms(nod, checked);
    tmp = checked->first;
    i = 0;
    launch_path2(path2, nod, tmp);
    ft_printf(RED"path2=%s\n"EOC, path2->path[path2->k]);
    ft_printf("k = %d | max = %d\n", path2->k, path2->max);
    tmp = tmp->next;
    path2->path[path2->k] = ft_strjoin(path2->path[path2->k], " ");
	path2->path[path2->k] = ft_strjoin(path2->path[path2->k], tmp->name);
    while (path2->k < path2->max)
    {
        tmp2 = find_child_pos(nod, tmp, i);
        if (tmp2->check == 1 || tmp2->start == 1)
            i++;
        else
        {
            fill_path(path2, tmp2);
            ft_printf(RED"path2=%s\n"EOC, path2->path[path2->k]);
            i = 0;
            tmp = next_room_path(checked, tmp2);
            if (tmp2->end == 1 && path2->k < path2->max)
            {
                path2->k++;
                tmp = checked->first;
                if (path2->k < path2->max)
                    path2->path[path2->k] = tmp->name;
            }
        }
    }
    print_paths(path2);
}