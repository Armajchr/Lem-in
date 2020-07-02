/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <armajchr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 12:31:36 by armajchr          #+#    #+#             */
/*   Updated: 2020/07/02 14:33:55 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void    ft_sort_path(t_path *path)
{
    char    *tmp;
    int     i;
    int     j;

    i = 0;
    j = 1;
    while (i < path->max - 1)
    {
        while (j < path->max)
        {
            if (ft_strlen(path->roads[i]) > (ft_strlen(path->roads[j])))
            {
                tmp = path->roads[i];
                path->roads[i] = path->roads[j];
                path->roads[j] = tmp;
            }
            else
                j++;
        }
        i++;
        j = i + 1;
    }
}

void    ft_sort_path2(t_path *path)
{
    int		i;
	int		j;
	char	**tmp;

	i = 0;
	tmp = path->roads;
	if (!(path->roads = (char **)malloc(sizeof(char *) * 
		(path->max) + 1)))
		return ;
    i = 0;
    j = 0;
	while (i < path->max)
    {

        if (tmp[i][0] == '\0')
            i++;
        else
        {
		    path->roads[j] = tmp[i];
            i++;
            j++;
        }
    }
    path->max = j;
	free(tmp);
}