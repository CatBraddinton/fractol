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
     data->min.re = interpolate(mouseRe, data->min.re, interpolation);
     data->min.im = interpolate(mouseIm, data->min.im, interpolation);
     data->max.re = interpolate(mouseRe, data->max.re, interpolation);
     data->max.im = interpolate(mouseIm, data->max.im, interpolation);
}

int		mouse_press(int button, int x, int y, t_data *data)
{
	if (data->params->zoom == 1.1 && button == MOUSE_SCROLL_DOWN)
		return (1);
	if (button == MOUSE_SCROLL_UP || button == MOUSE_SCROLL_DOWN)
	{
		data->params->move_x = x / (data->mlx->image_width / (data->max.re - data->min.re)) + data->min.re;
		data->params->move_y = data->max.im - y / (data->mlx->image_height / (data->max.im - data->min.im));
		data->params->center_x = (data->min.re + data->max.re) / 2.0;
		data->params->center_y = (data->min.im + data->max.im) / 2.0;
		data->params->offset_x = data->params->move_x - data->params->center_x;
		data->params->offset_y = data->params->move_y - data->params->center_y;
		data->min.re += data->params->offset_x;
		data->min.im += data->params->offset_y;
		data->max.re += data->params->offset_x;
		data->max.im += data->params->offset_y;
		if (button == MOUSE_SCROLL_UP)
		{
			data->params->zoom += 0.1;
			// data->params->max_iter = interpolate(data->params->max_iter,
			// 	data->params->max_iter * data->params->zoom,
			// 	1.0 / data->params->zoom);
			applyZoom(data, data->params->move_x, data->params->move_y, data->params->zoom);
		}
		else if (button == MOUSE_SCROLL_DOWN)
		{
			data->params->zoom -= 0.1;
			applyZoom(data, data->params->move_x, data->params->move_y, 1.0 / data->params->zoom);
		}
		printf("zoom = %lf, max = %d\n", data->params->zoom, data->params->max_iter);
		mlx_destroy_image(data->mlx->p_mlx, data->mlx->img);
		draw_fractals(data);
	}
	return (1);
}

int		mouse_move(int x, int y, t_data *data)
{
	if (data->type == 1 && x <= data->mlx->image_width && y <= data->mlx->image_height)
	{
		data->params->mouse_x = 4 * ((double)x / data->mlx->image_width - 0.5);
		data->params->mouse_y =
			4 * ((double)(data->mlx->image_height - y) / data->mlx->image_height - 0.5);
		set_complex(&(data->set->k), data->params->mouse_x, data->params->mouse_y);
		mlx_destroy_image(data->mlx->p_mlx, data->mlx->img);
		draw_fractals(data);
	}
	return (1);
}

int	key_press(int keycode, t_data *data)
{
	(void)data;
	if (keycode == ESC)
		exit(EXIT_SUCCESS);
	return (1);
}

int	close(int keycode)
{
	(void)keycode;
	exit(EXIT_SUCCESS);
}
