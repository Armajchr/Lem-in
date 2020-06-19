/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <armajchr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 11:53:29 by armajchr          #+#    #+#             */
/*   Updated: 2020/01/15 16:08:17 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		check_links_list(t_nod *tmp4, t_lst *list)
{
	int		ko;
	t_lst	*tmp5;

	tmp5 = list->first;
	ko = 0;
	while (ft_strcmp(tmp4->name, tmp5->name) != 0)
	{
		tmp5 = tmp5->next;
		if (tmp5 == NULL)
			return (1);
	}
	return (ko);
}

int		check_links_queue(t_lst *checked, t_nod *tmp4, int ko)
{
	t_lst	*tmp6;
	int		ko2;

	tmp6 = checked->first;
	ko2 = 0;
	if (tmp6 == NULL || ko == 0)
		return (1);
	if (ko == 1 && tmp6 != NULL)
	{
		while (ft_strcmp(tmp6->name, tmp4->name) != 0)
		{
			tmp6 = tmp6->next;
			if (tmp6 == NULL)
				return (1);
		}
	}
	return (ko2);
}

void	first_room(t_path *path, t_nod *nod, t_lst *tmp, int k)
{
	t_nod	*tmp2;

	tmp2 = nod->first;
	if (tmp2->start == 1)
	{
		path->path[k] = ft_strjoin(tmp2->name, " ");
		path->path[k] = ft_strjoin(path->path[k], tmp->name);
		return ;
	}
}

void	last_father(t_lst *list, t_lst *tmp2, t_nod *tmp4)
{
	t_lst	*tmp5;

	if (tmp4->end == 1)
	{
		tmp5 = list->first;
		while (ft_strcmp(tmp5->name, tmp4->name) != 0)
			tmp5 = tmp5->next;
		tmp5->father[tmp5->k++] = tmp2->next->name;
	}
}

int		fill_fathers_list(t_lst *tmp2, t_nod *tmp4, int k)
{
	tmp2->next->father[tmp2->next->k] = tmp4->name;
	tmp2->next->k++;
	k++;
	tmp2->next->check = 1;
	return (k);
}
