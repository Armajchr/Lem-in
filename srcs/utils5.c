/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <armajchr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 14:39:47 by armajchr          #+#    #+#             */
/*   Updated: 2020/06/24 16:15:32 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void get_to_find(t_path *path)
{
    int l;

    l = 0;
    ft_bzero((void *)path->to_find, 10);
    while (path->roads[path->i][path->j] != ' ')
        path->j++;
    path->j++;
    while (path->roads[path->i][path->j] != ' ')
    {
        path->to_find[l] = path->roads[path->i][path->j];
        l++;
        path->j++;
    }
    //ft_printf(PURPLE "to_find = %s\n" EOC, path->to_find);
    if (ft_strcmp(path->to_find, "start") == 0)
    {
        if ((path->i < (path->max - 1)) && (path->m < path->max))
        {
            path->i++;
            path->j = 0;
            path->m = path->i + 1;
            path->n = 0;
            ft_bzero((void *)path->to_find, 10);
        }
    }
}

void get_to_cmp(t_path *path)
{
    int l;

    l = 0;
    ft_bzero((void *)path->to_cmp, 10);
    while (path->roads[path->m][path->n] != ' ')
        path->n++;
    path->n++;
    while (path->roads[path->m][path->n] != ' ')
    {
        path->to_cmp[l] = path->roads[path->m][path->n];
        l++;
        path->n++;
    }
    if (ft_strcmp(path->to_cmp, "start") == 0)
    {
        if (path->m < path->max)
        {
            path->m++;
            path->n = 0;
            ft_bzero((void *)path->to_cmp, 10);
        }
    }
    ft_printf(PURPLE "to_cmp = {%s}\n" EOC, path->to_cmp);
}

void clear_paths_cmp(t_path *path)
{
    int count1;
    int count2;

    ft_printf("to_find = {%s}\n", path->to_find);
    if (ft_strcmp(path->to_find, path->to_cmp) == 0)
    {
        ft_printf("test\n");
        count1 = count_cap(path->roads[path->i]);
        count2 = count_cap(path->roads[path->m]);
        if (count1 < count2)
            path->roads[path->m] = "\0";
        else
            path->roads[path->i] = "\0";
        path->max--;
        if (((path->i) < (path->max - 1)) && ((path->m) < path->max))
        {
            path->i++;
            if (path->i >= (path->max - 1))
                return ;
            path->j = 0;
        }
        else
            return;
    }    
}

void final_paths_clear(t_path *path)
{
    while (path->i < (path->max - 1))
    {
        get_to_find(path);
        path->n = 0;
        path->m = path->i + 1;
        if (!ft_strequ(path->to_find, "start"))
        {
            // while ((path->i < (path->max - 1)) && (path->m < path->max))
            while (path->m < path->max)
            {
                get_to_cmp(path);
                if (path->to_find[0] && path->to_cmp[0])
                    clear_paths_cmp(path);
                if (path->m == path->max)
                {
                    path->m++;
                    path->n = 0;
                }
            }
        }  
    }
}

void paths_finder(t_nod *nod, t_lst *checked, t_path *path)
{
    t_path path2;
    char **tmp;
    int i;
    int j;

    path2 = init_path(&path2);
    second_fathers(nod, checked);
    get_paths(nod, checked, path);
    clear_paths(path);
    ft_printf("\n");
    get_paths2(nod, checked, &path2);
    clear_paths(&path2);
    tmp = path->roads;
    path->roads = (char **)malloc(sizeof(char *) * (path->k + path2.k));
    i = 0;
    while (i < path->k)
    {
        path->roads[i] = tmp[i];
        i++;
    }
    free(tmp);
    j = 0;
    while (j < path2.k)
    {
        path->roads[i] = (char *)malloc(sizeof(char) * (ft_strlen(path2.roads[j]) + 1));
        path->roads[i] = path2.roads[j];
        path->max++;
        i++;
        j++;
    }
    //clear_paths(path);
    //ft_printf("hello");
    //final_paths_clear(path);
    print_paths(path);
    ft_printf("\n");
}
