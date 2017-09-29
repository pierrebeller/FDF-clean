/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/29 10:14:56 by pbeller           #+#    #+#             */
/*   Updated: 2017/09/29 10:15:06 by pbeller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdlib.h>

void	del(void *content, size_t size)
{
	size = 0;
	free(content);
	content = NULL;
}

void	ft_free_structure(t_points *point)
{
	free(point);
}

void	ft_free_line(t_points **line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		ft_free_structure(line[i]);
		i++;
	}
	free(line[i]);
	free(line);
	line[i] = NULL;
}

void	ft_quit(t_window *window)
{
	int		i;

	i = 0;
	while (window->map[i])
	{
		ft_free_line(window->map[i]);
		i++;
	}
	free(window->map[i]);
	free(window->map);
	window->map[i] = NULL;
	ft_bzero(window->data, WIN_H * WIN_W * 4);
	mlx_clear_window(window->mlx, window->win);
	exit(0);
}
