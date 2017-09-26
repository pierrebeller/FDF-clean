/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 09:00:51 by pbeller           #+#    #+#             */
/*   Updated: 2017/03/06 09:00:58 by pbeller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_map(t_window *window)
{
	int x;
	int y;

	y = 0;
	while (y < window->map_h)
	{
		x = 0;
		while (x < window->map_w)
		{
			if (x < window->map_w - 1)
				draw_line(window, window->map[y][x], window->map[y][x + 1]);
			if (y < window->map_h - 1)
				draw_line(window, window->map[y][x], window->map[y + 1][x]);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(window->mlx, window->win, window->img, 0, 0);
}

void	draw_line(t_window *win, t_points *p1, t_points *p2)
{
	t_bresenham	*bres;

	bres = bres_build(p1, p2, win->max_z);
	if (bres->dx > bres->dy)
		ft_slow_increase(bres, win);
	else
		ft_high_increase(bres, win);
}

void	draw_point(t_window *win, int x, int y, int color)
{

	ft_memcpy(&win->data[(x * 4) + (y * win->size)], (const void *)&(color),
				(size_t)(sizeof(int)));
}

void	ft_slow_increase(t_bresenham *bres, t_window *window)
{
	int i;
	int color;

	color = 0x00FFFF00;
	bres->cumul = bres->dx / 2;
	i = 1;
	while (i <= bres->dx)
	{
		bres->x += bres->xinc;
		bres->cumul += bres->dy;
		if (bres->cumul >= bres->dx)
		{
			bres->cumul -= bres->dx;
			bres->y += bres->yinc;
		}
		if (check_x(bres->x) && check_y(bres->y))
		{
			draw_point(window, bres->x, bres->y,bres->color);
		}
		i++;
	}
}

void	ft_high_increase(t_bresenham *bres, t_window *window)
{
	int i;
	int color;

	color = 0x00FFFF00;
	bres->cumul = bres->dy / 2;
	i = 1;
	while (i <= bres->dy)
	{
		bres->y += bres->yinc;
		bres->cumul += bres->dx;
		if (bres->cumul >= bres->dy)
		{
			bres->cumul -= bres->dy;
			bres->x += bres->xinc;
		}
		if (check_x(bres->x) && check_y(bres->y))
		{
			draw_point(window, bres->x, bres->y, bres->color);
		}
		i++;
	}
}
