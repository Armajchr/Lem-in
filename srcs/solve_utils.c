/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <armajchr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 21:44:10 by tchivert          #+#    #+#             */
/*   Updated: 2020/07/01 15:41:31 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		count_cap(const char *s)
{
	int	i;
	int	cap;

	i = 1;
	cap = 1;
	while (s[i])
	{
		if (s[i] == ' ')
			cap++;
		i++;
	}
	return (cap);
}

void	free_res(t_way **way, char **ended, int paths)
{
	int		i;
	t_way	*head;
	t_way	*node;

	i = -1;
	while (++i < paths)
	{
		head = way[i];
		while (head)
		{
			node = head;
			head = head->next;
			ft_strdel(&node->name);
			ft_strdel(&node->endname);
			free(node);
		}
	}
	ft_strdel(ended);
}

t_way	*ft_create_node(t_way *next, char *name, char *end)
{
	t_way	*node;

	if (!(node = (t_way *)malloc(sizeof(t_way))))
		return (NULL);
	node->ant = 0;
	node->name = ft_strdup(name);
	node->endname = ft_strdup(end);
	if (!ft_strcmp(name, end))
		node->next = NULL;
	else
		node->next = next;
	return (node);
}

t_way	*ft_setpath(char **path, int path_nb, t_way **way)
{
	int		i;
	int		j;
	char	**names;

	i = -1;
	while (++i < path_nb)
	{
		j = -1;
		names = ft_strsplit(path[i], 32);
		while (names[++j])
			way[i] = ft_create_node(way[i], names[j], names[0]);
		while (--j < 0)
			ft_strdel(&names[j]);
		free(names);
	}
	return (*way);
}

int		select_next(char *ended, int next)
{
	int	i;

	if (next)
	{
		i = next;
		while (ended[i] == '1')
			i++;
		return (i + 1);
	}
	else
	{
		i = 0;
		while (ended[i] == '1')
			i++;
		return (i + 1);
	}
}
