/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <armajchr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 15:34:46 by armajchr          #+#    #+#             */
/*   Updated: 2020/06/23 15:09:45 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		child_position(t_lst *list, t_nod *tmp3)
{
	int		past;
	t_lst	*actual;

	past = 0;
	actual = list->first;
	while (actual)
	{
		if (ft_strcmp(actual->name, tmp3->name) == 0)
		{
			past = 1;
			break ;
		}
		actual = actual->next;
	}
	return (past);
}

void	print_paths(t_path *path)
{
	int		i;
	char	**tab;
	int		j;

	i = 0;
	while (i < path->max)
	{
		ft_printf(CYAN"path %d="EOC, i);
		tab = ft_strsplit(path->path[i], ' ');
		j = 0;
		while (tab[j])
			j++;
		j--;
		while (j >= 0)
		{
			ft_printf(CYAN" %s"EOC, tab[j]);
			j--;
		}
		ft_printf("\n");
		free(tab);
		i++;
	}
}

t_nod	*find_child_pos(t_nod *nod, t_lst *tmp, int i)
{
	t_nod	*tmp2;

	tmp2 = nod->first;
	while (ft_strcmp(tmp2->name, tmp->father[i]))
		tmp2 = tmp2->next;
	return (tmp2);
}

t_lst	*next_room_path(t_lst *checked, t_nod *tmp2)
{
	t_lst	*tmp;

	tmp = checked->first;
	while (ft_strcmp(tmp->name, tmp2->name) != 0)
		tmp = tmp->next;
	return (tmp);
}

t_lst	*get_paths3(t_path *path, t_nod *tmp2, t_lst *checked, t_nod *nod)
{
	t_lst	*tmp;

	tmp = next_room_path(checked, tmp2);
	if (tmp2->start == 1 && path->k < path->max)
	{
		path->k++;
		tmp = go_to_end(nod, checked);
		if (path->k < path->max)
			path->path[path->k] = tmp->name;
		else
			tmp->weight = 1;
	}
	return (tmp);
}
