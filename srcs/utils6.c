/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <armajchr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 11:33:01 by armajchr          #+#    #+#             */
/*   Updated: 2020/07/02 12:59:14 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	get_start_str(t_path *path, t_nod *nod)
{
	t_nod	*tmp;

	tmp = nod->first;
	while (tmp->start != 1)
		tmp = tmp->next;
	path->start = tmp->name;
}

void	cpy_path(t_path *path, t_path *path2)
{
	int		i;
	int		j;
	char	**tmp;

	i = -1;
	tmp = path->roads;
	if (!(path->roads = (char **)malloc(sizeof(char *) * 
		(path->k + path2->k) + 1)))
		return ;
	while (++i < path->k)
		path->roads[i] = tmp[i];
	free(tmp);
	j = 0;
	while (j < path2->k)
	{
		if (!(path->roads[i] = (char*)malloc(sizeof(char) *
				(ft_strlen(path2->roads[j])))))
			return ;
		path->roads[i] = path2->roads[j];
		path->max++;
		i++;
		j++;
	}
}

void	to_cmp_pos(t_path *path)
{
	int	l;

	l = 0;
	while (ft_isprint(path->roads[path->m][path->n])
			&& path->roads[path->m][path->n] != ' ')
	{
		path->to_cmp[l] = path->roads[path->m][path->n];
		l++;
		path->n++;
	}
	path->to_cmp[l] = '\0';
	if (ft_strcmp(path->to_cmp, path->start) == 0
			|| ft_strcmp(path->to_cmp, "L") == 0)
	{
		if (path->m < path->max)
		{
			path->m++;
			path->n = 0;
		}
	}
}

void	reset_pos(t_path *path)
{
	path->i = 0;
	path->j = 0;
	path->m = 1;
	path->n = 0;
	get_to_find(path);
	get_to_cmp(path);
}

void	get_to_find(t_path *path)
{
	int l;

	l = 0;
	path->n = 0;
	ft_bzero((void *)path->to_find, 10);
	if (path->j >= (int)ft_strlen(path->roads[path->i]))
	{
		path->i++;
		path->m = path->i + 1;
		path->j = 0;
	}
	while (path->roads[path->i][path->j] != ' ')
		path->j++;
	path->j++;
	while (path->roads[path->i][path->j] != ' ')
	{
		path->to_find[l] = path->roads[path->i][path->j];
		l++;
		path->j++;
	}
	path->to_find[l] = '\0';
}
