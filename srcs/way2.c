/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   way2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <armajchr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 11:34:38 by armajchr          #+#    #+#             */
/*   Updated: 2020/06/23 16:41:04 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		return_check(int l, t_nod *tmp, t_lst *tmp2)
{
	int	check;

	check = 0;
	while (l < tmp2->k)
	{
		if (ft_strcmp(tmp->name, tmp2->father[l]) == 0)
		{
			check = 0;
			break ;
		}
		else
			check = 1;
		l++;
	}
	return (check);
}

t_lst	*second_fathers_pos(t_lst *tmp2, t_nod *tmp, int i)
{
	while (ft_strcmp(tmp2->name, tmp->links[i]) != 0)
		tmp2 = tmp2->next;
	return (tmp2);
}

void	second_fathers_bis(int check, t_nod *tmp, t_lst *tmp2)
{
	if (check == 1)
	{
		tmp2->father[tmp2->k] = tmp->name;
		tmp2->k++;
	}
}

void	second_fathers(t_nod *nod, t_lst *checked)
{
	t_nod	*tmp;
	t_lst	*tmp2;
	int		i;
	int		l;
	int		check;

	rev_lst(nod);
	tmp = nod->first;
	tmp2 = checked->first;
	while (tmp)
	{
		i = 0;
		while (i < tmp->j)
		{
			tmp2 = second_fathers_pos(tmp2, tmp, i);
			l = 0;
			check = return_check(l, tmp, tmp2);
			second_fathers_bis(check, tmp, tmp2);
			i++;
			tmp2 = checked->first;
		}
		tmp = tmp->next;
	}
	//print_checked(checked);
	rev_lst(nod);
}
