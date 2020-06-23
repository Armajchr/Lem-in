/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <armajchr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 15:32:05 by armajchr          #+#    #+#             */
/*   Updated: 2020/06/23 16:41:03 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		ft_atoi_lem(const char *str)
{
	int	nb;
	int	i;

	nb = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	while (str[i] && ft_isdigit(str[i]) == 1)
	{
		if (nb > 2147483647 / 10)
			return (-1);
		nb *= 10;
		if (nb > 2147483647 - (str[i] - 48))
			return (-1);
		nb += str[i++] - 48;
	}
	return (nb);
}

void	ft_antnum(char *line, t_room *room)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (!ft_isdigit(line[i]))
			room->check = 2;
	}
	room->ants = ft_atoi_lem(line);
	if (room->ants == -1 || room->check == 2)
		room->check = 2;
	free(line);
}

void	ft_sharp(char *line, t_room *room)
{
	if (line[0] == 'L')
		room->check = 2;
	if (!ft_strcmp("##start", line))
		room->f |= (F_START);
	else if (!ft_strcmp("##end", line))
		room->f |= (F_END);
	free(line);
}

int		ft_no_start(t_nod *nod)
{
	t_nod	*tmp;
	int		count;

	count = 0;
	tmp = nod->first;
	while (tmp)
	{
		if (tmp->start == 1)
			count++;
		tmp = tmp->next;
	}
	if (count != 1)
		return (2);
	else
		return (1);
}
