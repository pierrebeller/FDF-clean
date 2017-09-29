/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 09:01:06 by pbeller           #+#    #+#             */
/*   Updated: 2017/03/06 09:01:08 by pbeller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	redraw(t_window *window)
{
	ft_bzero(window->data, WIN_H * WIN_W * 4);
	calcul_coords(window);
}

void	zoom_inc(t_window *window)
{
	window->pad += 1;
	redraw(window);
}

void	zoom_dec(t_window *window)
{
	if (window->pad > 1)
	{
		window->pad -= 1;
		redraw(window);
	}
}

void	projection(t_window *window)
{
	if(window->opt == ISO)
		window->opt = PARA;
	else if(window->opt == PARA)
		window->opt = ISO;
	redraw(window);
}

int		key_press(int keycode, t_window *window)
{
	if (keycode == 53)
	{
		/*mlx_clear_window(window->mlx, window->win);
		exit(0);*/
		ft_quit(window);
	}
	if (keycode == 30)
		zoom_inc(window);
	if (keycode == 33)
		zoom_dec(window);
	if (keycode == 123)
		move_l(window);
	if (keycode == 124)
		move_r(window);
	if (keycode == 126)
		move_u(window);
	if (keycode == 125)
		move_d(window);
	return (0);
}

int		key_hook(int keycode, t_window *window)
{
	if (keycode == 35)
		projection(window);
	return (0);
}