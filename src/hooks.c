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

// void	zoom(int keycode, t_data *data)
// {
// 	if (keycode == ZOOM_P)
// 	{
// 		data->cam.zoom += 0.1;
// 		count_fractal(data);
// 	}
// 	if (keycode == ZOOM_M)
// 	{
// 		if (data->cam.zoom > 0.1)
// 			data->cam.zoom -= 0.1;
// 		count_fractal(data);
// 	}
// }

int	key_press(int keycode, t_data *data)
{
	(void)data;
	// if (data->mlx_data->p_image)
	// 	mlx_destroy_image(data->mlx_data->p_mlx, data->mlx_data->p_image);
	if (keycode == ESC)
		exit(EXIT_SUCCESS);
	// if ((keycode == ZOOM_P) || (keycode == ZOOM_M))
	// 		zoom(keycode, data);
	return (0);
}

int	close(int keycode)
{
	(void)keycode;
	exit(EXIT_SUCCESS);
}
