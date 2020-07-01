/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <armajchr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 14:39:47 by armajchr          #+#    #+#             */
/*   Updated: 2020/07/01 15:30:31 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	get_to_cmp(t_path *path)
{
	ft_bzero((void *)path->to_cmp, 10);
	if (path->roads[path->m][0])
	{
		while (path->roads[path->m][path->n] != ' ')
			path->n++;
		path->n++;
	}
	else
		return ;
	if (path->n >= (int)ft_strlen(path->roads[path->m]))
	{
		path->m++;
		path->n = 0;
		if (path->m >= path->max)
			return ;
	}
	to_cmp_pos(path);
}

void	clear_paths_cmp(t_path *path)
{
	int	count1;
	int	count2;

	count1 = 0;
	count2 = 0;
	if (ft_strcmp(path->to_find, path->to_cmp) == 0)
	{
		count1 = count_cap(path->roads[path->i]);
		count2 = count_cap(path->roads[path->m]);
		if (count1 <= count2)
		{
			ft_bzero(path->roads[path->m], 2);
			path->roads[path->m] = "L\0";
		}
		else
		{
			ft_bzero(path->roads[path->i], 2);
			path->roads[path->i] = "L\0";
		}
		reset_pos(path);
	}
}

void	final_cleaning(t_path *path)
{
	int		i;
	int		count;
	int		j;
	char	**tmp;

	i = 0;
	count = 0;
	while (i < path->max)
	{
		if (ft_strcmp("L", path->roads[i]) == 0)
			count++;
		i++;
	}
	path->max -= count;
	tmp = path->roads;
	if (!(path->roads = (char **)malloc(sizeof(char *) * 
		(path->max) + 1)))
		return ;
	i = 0;
	j = 0;
	while (i < path->max)
	{
		if (ft_strcmp(tmp[j], "L") == 0)
			j++;
		else
		{
			if (!(path->roads[i] = (char*)malloc(sizeof(char) *
				(ft_strlen(tmp[j])))))
			return ;
			path->roads[i] = tmp[j];
			i++;
			j++;
		}
	}
	free(tmp);
}

void	final_paths_clear(t_path *path, t_nod *nod)
{
	get_start_str(path, nod);
	path->m = path->i + 1;
	while (path->i < (path->max - 1)
			&& path->j <= (int)ft_strlen(path->roads[path->max - 1]))
	{
		get_to_find(path);
		while (path->m < path->max)
		{
			if (path->m < path->max)
				get_to_cmp(path);
			if (path->to_find[0] && path->to_cmp[0]
					&& ft_strcmp(path->start, path->to_cmp) != 0)
				clear_paths_cmp(path);
			if (path->m >= path->max && path->i < path->max - 1)
			{
				path->m = path->i + 1;
				break ;
			}
			if (path->n > (int)ft_strlen(path->roads[path->m]))
				path->n = 0;
		}
		if (path->i >= (path->max - 1) && path->m >= path->max)
			break ;
	}
	final_cleaning(path);
}

void	paths_finder(t_nod *nod, t_lst *checked, t_path *path)
{
	t_path path2;

	path2 = init_path(&path2);
	second_fathers(nod, checked);
	get_paths(nod, checked, path);
	clear_paths(path);
	print_paths(path);
	path->k != -1 ? get_paths2(nod, checked, &path2) : 0;
	path2.k != -1 ? clear_paths(&path2) : 0;
	print_paths(&path2);
	path->k != -1  && path2.k != -1 ? cpy_path(path, &path2) : 0;
	if (path->k != -1  && path2.k != -1)
	{
		clear_paths(path);
		final_paths_clear(path, nod);
		ft_sort_path(path);
		print_paths(path);
		ft_printf("\n");
	}
}
