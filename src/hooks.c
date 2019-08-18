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

void	move(int keycode, t_data *data)
{
	if (keycode == UP)
		data->pos_up = (data->pos_up + 10) * data->zoom;
	if (keycode == DOWN)
		data->pos_up = (data->pos_down + 10) * data->zoom;
	if (keycode == LEFT)
		data->pos_up = (data->pos_left + 10) * data->zoom;
	if (keycode == RIGHT)
		data->pos_up = (data->pos_right + 10) * data->zoom;
}

void	zoom(int keycode, t_data *data)
{
	mlx_destroy_image(data->p_mlx, data->p_image);
	if (keycode == ZOOM_P)
		data->zoom = data->zoom + 0.5;
	else if (keycode == ZOOM_M)
		if (data->zoom > 0.5)
			data->zoom = data->zoom - 0.5;
	count_fractal(data);
}

int	key_press(int keycode, t_data *data)
{
	(void)data;
	if (keycode == ESC)
		exit(EXIT_SUCCESS);
	if (data->p_image != NULL)
	{
		if ((keycode == ZOOM_P) || (keycode == ZOOM_M))
			zoom(keycode, data);
		if ((keycode == UP) || (keycode ==DOWN) ||
			(keycode ==LEFT) || (keycode == RIGHT))
			move(keycode, data);
	}
	return (0);
}

int	close(int keycode)
{
	(void)keycode;
	exit(EXIT_SUCCESS);
}
