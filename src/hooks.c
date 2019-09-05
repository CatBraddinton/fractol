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
//
// int	key_press(int keycode, t_data *data)
// {
// 	if (keycode == ESC)
// 		exit(EXIT_SUCCESS);
// 	if (data->p_image != NULL)
// 	{
// 		mlx_destroy_image(data->p_mlx, data->p_image);
// 		if (keycode == ZOOM_P)
// 			data->cam->zoom += 0.1;
// 		if (keycode == ZOOM_M)
// 			if (data->cam->zoom > 0)
// 				data->cam->zoom -= 0.1;
// 		if (keycode == LEFT)
// //			if (data->cam->offset_x > 10)
// 				data->cam->offset_x += 10;
// 		if (keycode == RIGHT)
// //			if (data->cam->offset_x < WIDTH)
// 				data->cam->offset_x -= 10;
// 		if (keycode == UP)
// //			if (data->cam->offset_y > 10)
// 				data->cam->offset_y += 10;
// 		if (keycode == DOWN)
// //			if (data->cam->offset_y < HEIGHT)
// 				data->cam->offset_y -= 10;
// 		// if ((keycode == UP) || (keycode ==DOWN) ||
// 		// 	(keycode ==LEFT) || (keycode == RIGHT))
// 		// 	move(keycode, data);
// 		draw_fractals(data);
// 	}
// 	return (1);
// }

int	close(int keycode)
{
	(void)keycode;
	exit(EXIT_SUCCESS);
}
