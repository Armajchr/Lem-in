/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <armajchr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 12:09:05 by armajchr          #+#    #+#             */
/*   Updated: 2020/06/24 14:19:08 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	get_fathers(t_lst *list, t_nod *nod, t_lst *checked, t_lst *tmp2)
{
	t_nod	*tmp3;
	t_nod	*tmp4;
	int		k;

	if (tmp2->next->check == 0)
	{
		k = 0;
		tmp3 = nod->first;
		while (ft_strcmp(tmp3->name, tmp2->next->name) != 0)
			tmp3 = tmp3->next;
		while (k < tmp3->j)
		{
			tmp4 = nod->first;
			while (ft_strcmp(tmp4->name, tmp3->links[k]) != 0)
				tmp4 = tmp4->next;
			k = search_fathers(list, checked, tmp4, tmp2, k);
		}
	}
}

void	get_childs(t_lst *list, int i, t_nod *nod, t_lst *checked)
{
	t_nod	*tmp;
	t_lst	*tmp2;
	t_nod	*tmp3;
	int		past;

	past = 0;
	tmp = nod->first;
	while (ft_strcmp(tmp->name, list->first->name) != 0)
		tmp = tmp->next;
	while (i < tmp->j)
	{
		tmp3 = nod->first;
		while (ft_strcmp(tmp3->name, tmp->links[i]) != 0)
			tmp3 = tmp3->next;
		past = child_position(list, tmp3);
		if (past == 1 || tmp3->check == 1)
			i++;
		else
		{
			tmp2 = ft_list_push_back(list, tmp, i);
			i++;
			get_fathers(list, nod, checked, tmp2);
		}
	}
}

void	check_room(t_lst *list, t_nod *nod, t_lst *checked)
{
	t_nod	*thisistheway;
	t_lst	*tmp2;

	thisistheway = nod->first;
	tmp2 = list->first;
	while (ft_strcmp(tmp2->name, thisistheway->name) != 0)
		thisistheway = thisistheway->next;
	thisistheway->check = 1;
	ft_list_push_end(checked, thisistheway, list);
	list->first = tmp2->next;
	free(tmp2);
	tmp2 = NULL;
}

void	get_paths(t_nod *nod, t_lst *checked, t_path *path)
{
	t_lst	*tmp;
	t_nod	*tmp2;
	t_nod	*tmp3;
	int		i;

	clear_checked_rooms(nod, checked);
	tmp = go_to_end(nod, checked);
	tmp3 = nod->first;
	while (ft_strcmp(tmp3->name, tmp->name) != 0)
		tmp3 = tmp3->next;
	if (tmp3->end != 1)
	{
		path->k = -1;
		ft_printf("\nlemin: error: no path");
		return ;
	}
	i = 0;
	launch_path(path, tmp);
	while (path->k < path->max)
	{
		tmp2 = find_child_pos(nod, tmp, i);
		if (tmp2->check == 1 || tmp2->end == 1)
		{
			i++;
			if (i >= tmp->k)
			{
				path->max--;
				i = 0;
				tmp = go_to_end(nod, checked);
				path->roads[path->k] = tmp->name;
			}
		}
		else
		{
			fill_path(path, tmp2);
			tmp = get_paths3(path, tmp2, checked, nod);
			if (tmp->weight == 1)
				return ;
			i = 0;
		}
	}
}

void	get_paths2(t_nod *nod, t_lst *checked, t_path *path2)
{
	t_lst	*tmp;
	t_nod	*tmp2;
	t_nod	*tmp3;
	int		i;
	clear_checked_rooms(nod, checked);
	tmp = go_to_end(nod, checked);
	tmp->weight = 0;
	tmp3 = nod->first;
	while (ft_strcmp(tmp3->name, tmp->name) != 0)
		tmp3 = tmp3->next;
	if (tmp3->end != 1)
	{
		path2->k = -1;
		ft_printf("lemin: error: no path");
		return ;
	}
	i = tmp->k - 1;
	launch_path(path2, tmp);
	while (path2->k < path2->max)
	{
		tmp2 = find_child_pos(nod, tmp, i);
		if (tmp2->check == 1 || tmp2->end == 1)
		{
			i--;
			if (i == -1)
			{
				path2->max--;
				tmp = go_to_end(nod, checked);
				i = tmp->k - 1;
				path2->roads[path2->k] = tmp->name;
			}
		}
		else
		{
			fill_path(path2, tmp2);
			tmp = get_paths3(path2, tmp2, checked, nod);
			i = tmp->k - 1;
			if (tmp->weight == 1)
				return ;
		}
	}
}

void	bfs4(t_nod *nod, t_lst *list, t_lst *checked)
{
	t_nod	*tmp;
	t_lst	*tmp2;
	char	*room;
	int		i;

	i = 0;
	tmp = get_room_start(nod);
	room = tmp->name;
	tmp2 = list->first;
	if (!(tmp2 = ft_create_elem2(list)))
		return ;
	tmp2->name = tmp->name;
	list->first = tmp2;
	while (list)
	{
		get_childs(list, i, nod, checked);
		check_room(list, nod, checked);
		if (list->first == NULL)
			break ;
		room = list->first->name;
		tmp = get_room_position(nod, room);
	}
}
