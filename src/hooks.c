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

double interpolate(double start, double end, double interpolation)
{
    return start + ((end - start) * interpolation);
}

void applyZoom(t_data *data, double mouseRe, double mouseIm, double zoomFactor)
{
     double interpolation = 1.0 / zoomFactor;
     data->re_min = interpolate(mouseRe, data->re_min, interpolation);
     data->im_min = interpolate(mouseIm, data->im_min, interpolation);
     data->re_max = interpolate(mouseRe, data->re_max, interpolation);
     data->im_max = interpolate(mouseIm, data->im_max, interpolation);
}

int		mouse_press(int button, int x, int y, t_data *data)
{
	if (button == MOUSE_SCROLL_UP || button == MOUSE_SCROLL_DOWN)
	{
		data->params->move_x = x / (data->image_width / (data->re_max - data->re_min)) + data->re_min;
		data->params->move_y = data->im_min - y / (data->image_height / (data->im_max - data->im_min));
		if (button == ZOOM_P || button == MOUSE_SCROLL_UP)
		{
			data->params->zoom += 0.1;
			applyZoom(data, data->params->move_x, data->params->move_y, data->params->zoom);
			data->params->center_x = fabs(data->re_max) + fabs(data->re_min) / 2.0;
			data->params->center_y = fabs(data->im_max) + fabs(data->im_min) / 2.0;
			data->im_offset_x = data->params->move_x - data->params->center_x;
			data->im_offset_y = data->params->move_y - data->params->center_y;
		}
		else if (button == ZOOM_M || button == MOUSE_SCROLL_DOWN)
			if (data->params->zoom > 0.1)
			{
				data->params->zoom -= 0.1;
				applyZoom(data, data->params->move_x, data->params->move_y, 1.0 / data->params->zoom);
			}
	}
	mlx_destroy_image(data->mlx->p_mlx, data->mlx->p_img);
	draw_fractals(data);
	return (1);
}

int		mouse_move(int x, int y, t_data *data)
{
	if (data->type == 1 && x <= data->image_width && y <= data->image_height)
	{
		data->params->mouse_x = 4 * ((double)x / data->image_width - 0.5);
		data->params->mouse_y =
			4 * ((double)(data->image_height - y) / data->image_height - 0.5);
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
