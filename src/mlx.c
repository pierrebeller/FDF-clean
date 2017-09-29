/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 09:01:06 by pbeller           #+#    #+#             */
/*   Updated: 2017/03/06 09:01:08 by pbeller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		ft_create_window(t_window *window)
{
	window->mlx = mlx_init();
	window->win = mlx_new_window(window->mlx, WIN_W, WIN_H, "fdf");
	window->pad = 1;
	window->opt = ISO;
	window->pad_h = 1;
	window->move_lr = 0;
	window->move_ud = 0;
	//win->draw_type = PUT;
	window->angle = 0;
	window->rot = BET_Z;
	window->legend = ON;
	window->map_w = 0;
	window->img = mlx_new_image(window->mlx, WIN_W, WIN_H);
	window->data = mlx_get_data_addr(window->img,\
	&(window->color), &(window->size), &(window->endian));
	window->map = ft_fdf(window);
}

void		ft_do_fdf(t_window *window)
{
	ft_create_window(window);
	calcul_coords(window);
	//mlx_key_hook(window->win, key_hook, window);
	mlx_hook(window->win, 2, (1L << 0), key_press, window);
	//mlx_hook(window->win, 3, (1L << 1), key_release, window);
	//mlx_mouse_hook(window->win, mouse_hook, window);
	//mlx_expose_hook(window->win, expose_hook, window);
	mlx_loop(window->mlx);
}
