/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdudko <kdudko@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 23:57:08 by kdudko            #+#    #+#             */
/*   Updated: 2019/08/14 23:57:09 by kdudko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

void	zoom(int keycode, t_data *data)
{
	if (keycode == ZOOM_P || keycode == MOUSE_SCROLL_UP)
		data->params->zoom += 1.0;
	else if (keycode == ZOOM_M || keycode == MOUSE_SCROLL_DOWN)
		data->params->zoom -= 1.0;
}

int		mouse_press(int button, int x, int y, t_data *data)
{
	if (button == MOUSE_SCROLL_UP || button == MOUSE_SCROLL_DOWN)
	{
		data->params->move_x = x;
		data->params->move_y = y;
		zoom(button, data);
	}
	mlx_destroy_image(data->mlx->p_mlx, data->mlx->p_img);
	draw_fractals(data);
	return (1);
}

int		mouse_move(int x, int y, t_data *data)
{
	data->params->mouse_x = 4 * ((double)x / WIDTH - 0.5);
	data->params->mouse_y = 4 * ((double)(HEIGHT - y) / HEIGHT - 0.5);
	if (data->type == 1)
	{
		set_complex(&(data->set.k), data->params->mouse_x, data->params->mouse_y);
		mlx_destroy_image(data->mlx->p_mlx, data->mlx->p_img);
		draw_fractals(data);
	    return (0);
	}
	return (1);
}


void	move(int keycode, t_data *data)
{
	if (keycode == UP)
		data->params->move_y -= 0.01 ;
	if (keycode == DOWN)
		data->params->move_y += 0.01;
	if (keycode == LEFT)
		data->params->move_x -= 0.01;
	if (keycode == RIGHT)
		data->params->move_x += 0.01;
}

int	key_press(int keycode, t_data *data)
{
	(void)data;
	if (keycode == ESC)
		exit(EXIT_SUCCESS);
	if (data->mlx->p_img)
	{
		if (keycode == ZOOM_P || keycode == ZOOM_M)
			zoom(keycode, data);
		if (keycode == UP || keycode == DOWN || keycode == LEFT ||
			keycode == RIGHT)
			move(keycode, data);
		mlx_destroy_image(data->mlx->p_mlx, data->mlx->p_img);
		draw_fractals(data);
	}
	return (1);
}

int	close(int keycode)
{
	(void)keycode;
	exit(EXIT_SUCCESS);
}
