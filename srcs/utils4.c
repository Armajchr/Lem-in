/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <armajchr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 15:09:34 by armajchr          #+#    #+#             */
/*   Updated: 2020/06/18 16:18:59 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_nod	*get_room_start(t_nod *nod)
{
	t_nod	*tmp;

	tmp = nod->first;
	while (tmp->start != 1)
		tmp = tmp->next;
	return (tmp);
}

t_nod	*get_room_position(t_nod *nod, char *room)
{
	t_nod	*tmp;

	tmp = nod->first;
	while (ft_strcmp(tmp->name, room) != 0)
		tmp = tmp->next;
	return (tmp);
}

void	clear_paths(t_path *path)
{
	int	i;
	int	j;
	int	count;

	count = 0;
	i = 0;
	while (i < path->max - 1)
	{
		j = i + 1;
		while (j < path->max)
		{
			if (ft_strcmp(path->path[i], path->path[j]) == 0
					&& path->path[j][0] != '\0')
			{
				path->path[j] = "\0";
				count++;
			}
			j++;
		}
		i++;
	}
	path->max -= count;
}
