/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <armajchr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 18:24:42 by tchivert          #+#    #+#             */
/*   Updated: 2020/07/02 11:59:51 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_way	*ft_printl(t_resolv *turn, t_way **way, t_way *ptr, char *ended)
{
	ft_printf("L%d-%s ", ptr->ant, ptr->next->name);
	if (!ft_strcmp(ptr->name, way[turn->i]->name))
		turn->start++;
	if (!ft_strcmp(ptr->next->name, ptr->endname))
	{
		ended[ptr->ant - 1] = '1';
		turn->end++;
	}
	turn->next = select_next(ended, ptr->ant);
	ptr->next->ant = ptr->ant;
	ptr->ant = 0;
	turn->move--;
	if (turn->i < turn->max - 1)
		turn->i++;
	else
		turn->i = 0;
	return (way[turn->i]);
}

void	play_turn(t_resolv *turn, t_way **way, t_way *ptr, char **ended)
{
	turn->i = 0;
	turn->move = (turn->start - turn->end);
	if (turn->move != turn->max && turn->start < turn->ants)
		turn->move += turn->max - 1;
	turn->next = select_next(*ended, 0);
	ptr = way[turn->i];
	while (turn->move && turn->next <= turn->ants)
	{
		if (ptr->ant == turn->next)
		{
			ptr = ft_printl(turn, way, ptr, *ended);
			ptr->ant = turn->start;
		}
		else if (ptr->next)
			ptr = ptr->next;
		else
		{
			if (turn->i < turn->max - 1)
				turn->i++;
			else
				turn->i = 0;
			ptr = way[turn->i];
		}
	}
}

int		select_paths(t_path path, int ants)
{
	int	i;
	int	j;
	int	cap;
	int	prev_cap;

	i = -1;
	cap = 0;
	while (path.roads[++i] && cap <= ants && i < path.max)
	{
		j = -1;
		prev_cap = cap;
		cap = 0;
		while (++j < i)
			cap += count_cap(path.roads[j]) - 1;
		if (cap > ants && ((cap - ants) > (ants - prev_cap)))
			i--;
	}
	return (i);
}

void	print_res(t_path path, int ants)
{
	int			i;
	t_resolv	turn;
	t_way		*way[path.max];
	t_way		ptr;
	char		*ended;

	i = -1;
	if (!(ended = malloc(sizeof(char) * ants + 1)))
		return ;
	while (++i < ants)
		ended[i] = '0';
	turn.ants = ants;
	turn.end = 0;
	turn.start = 1;
	turn.max = select_paths(path, ants);
	ft_setpath(path.roads, turn.max, &*way);
	way[0]->ant = 1;
	turn.move = turn.max;
	while (turn.end < ants)
	{
		play_turn(&turn, &*way, &ptr, &ended);
		ft_printf("\n");
	}
	free_res(&*way, &ended, turn.max);
}
