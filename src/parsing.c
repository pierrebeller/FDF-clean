/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 09:01:06 by pbeller           #+#    #+#             */
/*   Updated: 2017/03/06 09:01:08 by pbeller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"

t_points	*ft_newpoint(char *data, int y, int index, t_window *win)
{
	t_points *point;

	point = malloc(sizeof(t_points));
	point->x = index;
	point->y = y;
	point->z = ft_atoi(data);
	if (point->z > win->max_z)
		win->max_z = point->z;
	return (point);
}

t_points	**ft_new_line(char *line, int y, t_window *win)
{
	t_points	**bigline;
	char		**tab;
	int			index;

	index = 0;
	bigline = malloc(sizeof(t_points *) * ft_strlen(line) + 1);
	tab = ft_strsplit(line, ' ');
	while (tab[index])
	{
		bigline[index] = ft_newpoint(tab[index], y, index, win);
		index++;
	}
	if (index > win->map_w)
		win->map_w = index;
	bigline[index] = NULL;
	return (bigline);
}

t_points	***ft_create_map(t_list *map, t_window *win)
{
	t_points	***tab;
	int			y;

	y = 0;
	tab = malloc(sizeof(t_points **) * (ft_lstlen(map) + 1));
	while (map)
	{
		tab[y] = ft_new_line(map->content, y, win);
		y++;
		map = map->next;
	}
	win->map_h = y;
	tab[y] = NULL;
	return (tab);
}

t_points	***ft_fdf(t_window *win)
{
	int			fd;
	char		*line;
	t_list		*map;
	t_points	***tab;

	map = NULL;
	if (!(fd = open(win->path, O_RDONLY)))
		exit(0);
	while (get_next_line(fd, &line))
	{
		if (!line)
		{
			ft_putstr_fd("Invalide map\n", 2);
			exit(1);
		}
		ft_lst_push_back(&map, ft_lstnew(ft_strdup(line), ft_strlen(line)));
		free(line);
	}
	tab = ft_create_map(map, win);
	free(map);
	return (tab);
}
