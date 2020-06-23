/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <armajchr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 14:39:47 by armajchr          #+#    #+#             */
/*   Updated: 2020/06/23 16:06:20 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	paths_finder(t_nod *nod, t_lst *checked, t_path *path)
{
    t_path  path2;
    int     i;
    int     j;

    path2 = init_path(&path2);
	second_fathers(nod, checked);
	get_paths(nod, checked, path);
	clear_paths(path);
	ft_printf("\n");
	get_paths2(nod, checked, &path2);
	clear_paths(&path2);
   /* i = path->k;
    j = 0;
    while (j < path2.k)
    {
        path->path[i] = (char*)malloc(sizeof(char) * ft_strlen(path2.path[j]) + 1);
        path->path[i] = path2.path[j];
        path->max++;
        i++;
        j++;
    }*/
    //print_paths(path);
    //ft_printf("\n");
}
