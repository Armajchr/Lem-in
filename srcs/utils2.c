/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <armajchr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 12:46:08 by armajchr          #+#    #+#             */
/*   Updated: 2020/06/18 16:18:39 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		search_fathers(t_lst *list, t_lst *checked, t_nod *tmp4, t_lst *tmp2, int k)
{
	int	ko;
	int	ko2;

	ko = check_links_list(tmp4, list);
	ko2 = check_links_queue(checked, tmp4, ko);
	if (ko == 0 || ko2 == 0)
	{
		k = fill_fathers_list(tmp2, tmp4, k);
		last_father(list, tmp2, tmp4);
	}
	else
		k++;
	return (k);
}

void	clear_checked_rooms(t_nod *nod, t_lst *checked)
{
	t_lst	*tmp;
	t_nod	*tmp2;

	tmp = checked->first;
	tmp2 = nod->first;
	while (tmp)
	{
		tmp->check = 0;
		tmp = tmp->next;
	}
	tmp = checked->first;
	while (tmp2)
	{
		tmp2->check = 0;
		tmp2 = tmp2->next;
	}
}

t_lst	*go_to_end(t_nod *nod, t_lst *checked)
{
	t_lst	*tmp;
	t_nod	*tmp2;

	tmp = checked->first;
	tmp2 = nod->first;
	while (tmp->next)
	{
		tmp2 = nod->first;
		while (ft_strcmp(tmp2->name, tmp->name) != 0)
			tmp2 = tmp2->next;
		if (tmp2->end == 1)
			break ;
		tmp = tmp->next;
	}
	return (tmp);
}

void	fill_path(t_path *path, t_nod *tmp2)
{
	path->path[path->k] = ft_strjoin(path->path[path->k], " ");
	path->path[path->k] = ft_strjoin(path->path[path->k], tmp2->name);
	path->len++;
	tmp2->check = (tmp2->end == 1 || tmp2->start == 1) ? 0 : 1;
}

void	launch_path(t_path *path, t_lst *tmp)
{
	path->max = tmp->k;
	if (!(path->path = (char**)malloc(sizeof(char*) * tmp->k)))
		return ;
	path->path[path->k] = tmp->name;
}
