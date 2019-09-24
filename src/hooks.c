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

void zoom(t_data *data, double mouse_x, double mouse_y, double zoom_factor)
{
     double interpolation = 1.0 / zoom_factor;
     data->min.re = interpolate(mouse_x, data->min.re, interpolation);
     data->min.im = interpolate(mouse_y, data->min.im, interpolation);
     data->max.re = interpolate(mouse_x, data->max.re, interpolation);
     data->max.im = interpolate(mouse_y, data->max.im, interpolation);
}

int		mouse_press(int button, int x, int y, t_data *data)
{
	if (button != MOUSE_SCROLL_UP && button != MOUSE_SCROLL_DOWN)
		return (0);
	if (data->params->zoom == 1.1 && button == MOUSE_SCROLL_DOWN)
		return (1);
	if (x < data->mlx->image_width && y < data->mlx->image_height)
	{
		data->set->move.re = data->min.re + x * data->set->factor.re;
		data->set->move.im = data->max.im - y * data->set->factor.im;
		if (button == MOUSE_SCROLL_UP)
		{
			data->params->zoom += 0.1;
			data->params->zoom_factor = data->params->zoom;
		}
		if (button == MOUSE_SCROLL_DOWN)
		{
			data->params->zoom -= 0.1;
			data->params->zoom_factor = 1.0 / data->params->zoom;
		}
		zoom(data, data->set->move.re, data->set->move.im, data->params->zoom_factor);
		//mlx_destroy_image(data->mlx->p_mlx, data->mlx->img);
		draw_fractals(data);
	}
	return (1);
}

int		julia_motion(int x, int y, t_data *data)
{
	if (data->type == julia && x <= data->mlx->image_width && y <= data->mlx->image_height)
	{
		data->set->mouse.re = 4 * ((double)x / data->mlx->image_width - 0.5);
		data->set->mouse.im =
			4 * ((double)(data->mlx->image_height - y) / data->mlx->image_height - 0.5);
		set_complex(&(data->set->k), data->set->mouse.re, data->set->mouse.im);
		mlx_destroy_image(data->mlx->p_mlx, data->mlx->img);
		expose_hook(data);
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
