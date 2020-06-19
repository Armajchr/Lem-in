/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <armajchr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 17:00:12 by armajchr          #+#    #+#             */
/*   Updated: 2020/06/18 16:21:29 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		ft_parserr(int step, t_room *room)
{
	int	err;

	err = 0;
	if (step == 2 && (!room->ants || room->links))
		err = 1;
	else if (step == 3 && (!room->ants || !room->rooms))
		err = 1;
	return (err > 0 ? 1 : 0);
}

int		ft_parse(t_nod *nod, t_room *room)
{
	char	*line;

	while (get_next_line(0, &line))
	{
		if (line[0])
			ft_printf("%s\n", line);
		if (!room->ants)
			ft_antnum(line, room);
		else if (line[0] == '#' || line[0] == 'L')
			ft_sharp(line, room);
		else if (ft_strchr(line, ' ') && !ft_parserr(2, room) && room->check != 2)
			get_name_xy(line, room, nod);
		else if (ft_strchr(line, '-') && line[0] != '-'
				&& !ft_parserr(3, room) && room->check != 2)
		{
			if (!get_links1(room, line, nod) || !get_links2(room, nod))
				room->check = 2;
		}
		else
			room->check = 2;
	}
	room->check = (room->check == 2 || ft_parserr(3, room) ? 2 : 1);
	free(line);
	parsing_lem(room, nod);
	return (room->check == 2 ? 0 : 1);
}

int		main(void)
{
	t_nod	nod;
	t_room	room;
	t_lst	list;
	t_path	path;
	t_lst	checked;
	t_path	path2;

	ft_bzero(&room, sizeof(t_room));
	nod = init_stack(&nod);
	if (!ft_parse(&nod, &room) || room.check != 1|| ft_no_start(&nod) == 2)
	{
		ft_printf("\nlemin: fatal error: invalid map\n");
		return (0);
	}
	rev_lst(&nod);
	//print_info(&nod);
	list = init_list(&list);
	checked = init_list(&checked);
	path = init_path(&path);
	path2 = init_path(&path2);
	(room.check == 1) ? bfs4(&nod, &list, &checked, &path, &path2) : 0;
	(path.k == -1) ? 0 : print_res(path, room.ants);
	//(room.check == 1) ? visu(&nod, &path, &room) : 0;
	return (0);
}
