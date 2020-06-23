/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   novisulem_in.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <armajchr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 12:46:36 by armajchr          #+#    #+#             */
/*   Updated: 2020/06/23 16:41:09 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# include "../Libft/libft.h"
# include "../ft_printf/ft_printf.h"
# include "../Libft/get_next_line.h"
# include <unistd.h>
# include <stdio.h>
# include <math.h>
/*# include <SDL2/SDL.h>
# include <SDL2/SDL_timer.h>
# include <SDL2_image/SDL_image.h>
# include <SDL2_ttf/SDL_ttf.h>
# include <SDL2_mixer/SDL_mixer.h>*/

# define F_START	1
# define F_END		2

typedef struct		s_room
{
	char			**tab;
	int				ants;
	int				rooms;
	int				links;
	int				f;
	int				check;
	int				len_path;
	int				rooms_nb;
	int				links_nb;
}					t_room;

typedef struct		s_nod
{
	struct s_nod	*first;
	struct s_nod	*next;
	char			*name;
	int				x;
	int				y;
	int				start;
	int				end;
	int				j;
	char			*links[100];
	int				check;
	int				weight;
}					t_nod;

typedef struct		s_lst
{
	struct s_lst	*first;
	struct s_lst	*next;
	char			*name;
	char			*father[100];
	int				k;
	int				weight;
	int				check;
}					t_lst;

typedef struct		s_path
{
	char			**path;
	int				len;
	int				max;
	int				k;
}					t_path;

typedef struct		s_way
{
	int				ant;
	int				ants_nb;
	char			*name;
	char			*endname;
	struct s_way	*next;
}					t_way;

typedef struct		s_resolv
{
	int				i;
	int				ants;
	int				end;
	int				start;
	int				move;
	int				next;
	int				max;
}					t_resolv;
/*
typedef struct		s_visu
{
	SDL_Window		*screen;
	int				isquit;
	SDL_Rect		src;
	SDL_Rect		dst;
	SDL_Rect		src1;
	SDL_Rect		dst1;
	SDL_Rect		src2;
	SDL_Rect		dst2;
	SDL_Event		event;
	SDL_Renderer	*renderer;
	SDL_Surface		*bmp;
	TTF_Font		*font;
	SDL_Surface		*text;
	SDL_Texture		*texture;
	SDL_Texture		*bmptexture;
	SDL_Surface		*small;
	SDL_Rect		pos_small;
	SDL_Rect		position;
	SDL_Color		color;
	SDL_Color		color2;
	SDL_Surface		*text2;
	SDL_Texture		*texture2;
	SDL_Rect		position2;
	SDL_Surface		*rooms[100];
	SDL_Texture		*names[100];
	SDL_Rect		coords[100];
	SDL_Point		points[100];
	SDL_Rect		rect[100];
	SDL_Point		point[100];
	int				i;
	int				j;
	int				k;
	int				l;
	SDL_Surface		*text3[10];
	SDL_Texture		*counter[50];
	SDL_Rect		position3;
	char			ant_left[100];
	SDL_Rect		dark_rect;
	int				count;
	int				check;
	int				move;
	SDL_Rect		pos_start;
	SDL_Rect		pos_end;
	int				x;
	int				y;
	int				index;
	int				actual;
	int				end;
}					t_visu;*/

t_nod				init_stack(t_nod *nod);
t_lst				init_list(t_lst *list);
t_path				init_path(t_path *path);
void				rev_lst(t_nod *nod);
void				rev_lst2(t_lst *list);
void				ft_list_push_end(t_lst *checked, t_nod *thisistheway
						, t_lst *list);
t_lst				*ft_checked_last(t_lst *tmp, t_nod *thisistheway
						, t_lst *checked);
t_lst				*ft_list_push_back(t_lst *list, t_nod *tmp, int i);
void				print_info(t_nod *nod);
t_nod				*ft_create_elem(t_nod *elem);
t_lst				*ft_create_elem2(t_lst *list);
void				clear_checked_rooms(t_nod *nod, t_lst *checked);
t_lst				*go_to_end(t_nod *nod, t_lst *checked);
void				fill_path(t_path *path, t_nod *tmp2);
void				launch_path(t_path *path, t_lst *tmp);
void				print_paths(t_path *path);
void				print_checked(t_lst *checked);
void				get_map_info(t_nod *nod, t_room *room);
int					get_name_xy(char *line, t_room *room, t_nod *nod);
void				get_name2(t_room *room, t_nod *tmp);
int					get_links1(t_room *room, char *line,
						t_nod *nod);
int					get_links2(t_room *room, t_nod *nod);
void				parsing_name(t_room *room, t_nod *nod);
void				parsing_name2(t_room *room, t_nod *nod);
void				parsing_lem(t_room *room, t_nod *nod, char *line);
void				parsing_xy(t_room *room, t_nod *nod);
void				parsing_links(t_room *room, t_nod *nod);
void				ft_sharp(char *line, t_room *room);
void				ft_antnum(char *line, t_room *room);
int					ft_no_start(t_nod *nod);
void				get_fathers(t_lst *list, t_nod *nod,
						t_lst *checked, t_lst *tmp2);
int					search_fathers(t_lst *list,
						t_lst *checked, t_nod *tmp4,
							t_lst *tmp2, int k);
void				last_father(t_lst *list, t_lst *tmp2,
						t_nod *tmp4);
int					fill_fathers_list(t_lst *tmp2,
						t_nod *tmp, int k);
void				get_childs(t_lst *list, int i, t_nod *nod
						, t_lst *checke);
int					child_position(t_lst *list,
						t_nod *tmp3);
void				check_room(t_lst *list, t_nod *nod,
						t_lst *checked);
int					check_links_list(t_nod *tmp4,
						t_lst *list);
int					check_links_queue(t_lst *checked,
						t_nod *tmp4, int ko);
void				get_paths(t_nod *nod, t_lst *checked,
						t_path *path);
void				get_paths2(t_nod *nod, t_lst *checked
						, t_path *path2);
int					get_path2(t_lst *checked, t_path *path,
						t_nod *tmp2, t_nod *nod);
void				bfs4(t_nod *nod, t_lst *list, t_lst *checked);
void				find_paths(t_path *path, t_nod *nod);
void				first_room(t_path *path, t_nod *nod
						, t_lst *tmp, int k);
t_nod				*find_child_pos(t_nod *nod, t_lst *tmp, int i);
t_lst				*next_room_path(t_lst *checked, t_nod *tmp2);
t_lst				*get_paths3(t_path *path, t_nod *tmp2,
						t_lst *checked, t_nod *nod);
t_nod				*get_room_start(t_nod *nod);
void				clear_paths(t_path *path);
t_nod				*get_room_position(t_nod *nod, char *room);
void				second_fathers(t_nod *nod, t_lst *checked);
int					return_check(int l, t_nod *tmp,
						t_lst *tmp2);
void				fast_path(t_nod *nod, t_lst *checked,
						t_path *path2);
void				print_res(t_path path, int ants);
int					count_cap(const char *s);
t_way				*ft_create_node(t_way *next, char *name, char *end);
t_way				*ft_setpath(char **path, int path_nb, t_way **way);
int					select_next(char *ended, int next);
void				free_res(t_way **way, char **ended, int paths);
void				second_fathers_bis(int check, t_nod *tmp, t_lst *tmp2);
t_lst				*second_fathers_pos(t_lst *tmp2, t_nod *tmp, int i);
void    			paths_finder(t_nod *nod, t_lst *checked, t_path *path);
/*
int					visu(t_nod *nod, t_path *path, t_room *room);
t_visu				init_visu(t_visu *visu, t_room *room,
						t_path *path);
t_visu				init_visu2(t_visu *visu, t_room *room,
						t_path *path);
t_visu				init_visu3(t_visu *visu);
t_visu				load_part1(t_visu *visu);
t_visu				load_part2(t_visu *visu, t_nod *nod,
						t_room *room);
t_visu				fill_points(t_visu *visu, t_nod *tmp,
						t_nod *nod, t_nod *tmp2);
t_visu				fill_rect(t_visu *visu, t_nod *tmp,
						t_room *room);
t_visu				load_items(t_visu *visu, t_nod *tmp,
						t_nod *nod, t_nod *tmp2);
void				render_part1(t_visu *visu, t_room *room);
void				render_part2(t_visu *visu, t_room *room);
void				render_part3(t_visu *visu, t_room *room);
void				render_destroy(t_visu *visu);
t_visu				nb_ants_screen(t_visu *visu, t_room *room);
t_visu				load_move(t_visu *visu, t_nod *nod,
						t_path *path, t_room *room);
t_visu				load_move_end(t_visu *visu, t_nod *tmp,
						t_path *path, t_room *room);
t_visu				load_move_mid(t_visu *visu, t_nod *tmp);
void				load_texture(t_visu *visu);
void				init_window(t_visu *visu, t_room *room,
						t_nod *nod, t_path *path);
void				visu_exec(t_visu *visu, t_nod *nod,
						t_path *path, t_room *room);
t_visu				init_src1_dst1(t_visu *visu);
t_visu				init_src2_dst2(t_visu *visu);*/
#endif
