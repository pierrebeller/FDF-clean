/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 09:01:06 by pbeller           #+#    #+#             */
/*   Updated: 2017/03/06 09:01:08 by pbeller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		calcul_coords(t_window *window)
{
	int i;
	int j;

	j = 0;
	while (j < window->map_h)
	{
		i = 0;
		while (i < window->map_w)
			calculate(window, window->map[j][i++]);
		j++;
	}
	draw_map(window);
}

void		calculate(t_window *window, t_points *point)
{
	if (window->opt == ISO)
	{
		point->new_x = window->pad * ((point->x) - (point->y))\
		+ WIN_W / 2 + window->move_lr;
		point->new_y = window->pad * ((point->x) + (point->y)) / 2\
		- window->pad_h * (point->z) + WIN_H / 4 + window->move_ud;
	}
	else if (window->opt == PARA)
	{
		point->new_x = window->pad * ((point->x - (point->z))) / 2\
		+ WIN_W / 2 + window->move_lr;
		point->new_y = window->pad * (point->y + point->z)\
		+ WIN_H / 3 + window->move_ud;
	}
}

t_bresenham	*bres_build(t_points *p1, t_points *p2, int max_z)
{
	t_bresenham *bres;

	bres = malloc(sizeof(t_bresenham));
	bres->x = p1->new_x;
	bres->y = p1->new_y;
	bres->dx = p2->new_x - p1->new_x;
	bres->dy = p2->new_y - p1->new_y;
	bres->xinc = (bres->dx > 0 ? 1 : -1);
	bres->yinc = (bres->dy > 0 ? 1 : -1);
	bres->dx = (bres->dx >= 0 ? bres->dx : -bres->dx);
	bres->dy = (bres->dy >= 0 ? bres->dy : -bres->dy);
	bres->delta_e = (bres->dx > bres->dy ? bres->dx : -(bres->dy)) / 2;
	bres->color = ft_paint(p1->z, p2->z, max_z);
	return (bres);
}

int			ft_paint(int p1, int p2, int max_z)
{
	if (((p1 + p2) * 500) > 500 * max_z)
		return (0xFFFFFF);
	else if (((p1 + p2) * 500) >= 50 * max_z && ((p1 + p2) * 500) < 200 * max_z)
		return (0x25FF50);
	else if (((p1 + p2) * 500) >= 10 * max_z && ((p1 + p2) * 500) < 50 * max_z)
		return (0xFFFF00);
	else if (((p1 + p2) * 500) < 10 * max_z)
		return (0x0041FF);
	else
		return (0xAD4F09);
}
