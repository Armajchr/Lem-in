/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   way2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <armajchr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 11:34:38 by armajchr          #+#    #+#             */
/*   Updated: 2020/06/18 16:10:37 by armajchr         ###   ########.fr       */
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
			while (ft_strcmp(tmp2->name, tmp->links[i]) != 0)
				tmp2 = tmp2->next;
			l = 0;
			check = return_check(l, tmp, tmp2);
			if (check == 1)
			{
				tmp2->father[tmp2->k] = tmp->name;
				tmp2->k++;
			}
			i++;
			tmp2 = checked->first;
		}
		tmp = tmp->next;
	}
	//print_checked(checked);
	rev_lst(nod);
}
