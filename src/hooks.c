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

// int		mouse_press(int button, int x, int y, t_data *data)
// {
// 	(void)data;
// 	(void)x;
// 	(void)y;
// 	(void)button;
// 	return (1);
// }
//
// int		mouse_move(int x, int y, t_data *data)
// {
// 	if (data->type == 1 && x < WIDTH && y < HEIGHT)
// 	{
// 		data->mouse_x = x;
// 		data->mouse_x = y;
// 	    draw_fractals(data);
// 	    return (0);
// 	}
// 	return (1);
// }
void	zoom(int keycode, t_data *data)
{
	if (keycode == ZOOM_P)
		data->params->zoom += 1.0;
	else if(keycode == ZOOM_M && data->params->zoom > 1)
		data->params->zoom -= 1.0;
}

void	move(int keycode, t_data *data)
{
	if (keycode == UP)
		data->params->move_y -= 0.005 * data->params->zoom;
	if (keycode == DOWN)
		data->params->move_y += 0.005 * data->params->zoom;
	if (keycode == LEFT)
		data->params->move_x -= 0.005 * data->params->zoom;
	if (keycode == RIGHT)
		data->params->move_x += 0.005 * data->params->zoom;
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
