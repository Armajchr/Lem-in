/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <armajchr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 17:00:12 by armajchr          #+#    #+#             */
/*   Updated: 2020/07/01 15:29:40 by armajchr         ###   ########.fr       */
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

char *savemap(char *map, char *line)
{
	static size_t total_size = 0;
	char	*tmp;

	total_size = total_size + ft_strlen(line) + 1;
	tmp = map;
	if (!(map = (char *)malloc(sizeof(char) * (total_size + 1))))
		return (NULL);
	*map = '\0';
	if (tmp)
		ft_strcpy(map, tmp);
	ft_strcat(map, line);
	if (tmp)
		free(tmp);
	map[total_size - 1] = '\n';
	map[total_size] = '\0';
	return (map);
}

void print_free(char *map, int ctl)
{
	(ctl != 2) ? ft_printf("%s", map) : 0;
	ft_strdel(&map);
}

int		ft_parse(t_nod *nod, t_room *room)
{
	char	*line;
	char	*map;
	int		ret;

	ret = 0 ;
	map = NULL;
	while ((ret = get_next_line(0, &line)) && room->check != 2)
	// while (get_next_line(0, &line))
	{
		if (ret == -1 || !(map = savemap(map, line)))
			return(0);
		// if (line[0] && !(map = ft_strreset(map,line)))
		if (!room->ants)
			ft_antnum(line, room);
		else if (line[0] == '#' || line[0] == 'L')
			ft_sharp(line, room);
		else if (ft_strchr(line, ' ') && !ft_parserr(2, room)
				&& room->check != 2)
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
	room->check = ft_no_start(nod, room);
	room->check = ft_no_end(nod, room);
	room->check = ft_no_tube(nod, room);
	parsing_lem(room, nod, line);
	print_free(map, room->check);
	return (room->check == 2 ? 0 : 1);
}

int		main(void)
{
	t_nod	nod;
	t_room	room;
	t_lst	list;
	t_path	path;
	t_lst	checked;

	ft_bzero(&room, sizeof(t_room));
	nod = init_stack(&nod);
	if (!ft_parse(&nod, &room) || room.check != 1 || ft_no_start(&nod, &room) == 2) 
		return (write(2, "ERROR\n", 6) ? 1 : 0);
	rev_lst(&nod);
	//print_info(&nod);
	list = init_list(&list);
	checked = init_list(&checked);
	path = init_path(&path);
	(room.check == 1) ? bfs4(&nod, &list, &checked) : 0;
	paths_finder(&nod, &checked, &path);
	(path.k == -1) ? 0 : print_res(path, room.ants);
	return (0);
}
