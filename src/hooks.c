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

double	interpolate(double start, double end, double interpolation)
{
	return (start + ((end - start) * interpolation));
}

void	zoom(t_data *data, double mouse_x, double mouse_y, double zoom_factor)
{
	double interpolation;

	interpolation = 1.0 / zoom_factor;
	data->min.re = interpolate(mouse_x, data->min.re, interpolation);
	data->min.im = interpolate(mouse_y, data->min.im, interpolation);
	data->max.re = interpolate(mouse_x, data->max.re, interpolation);
	data->max.im = interpolate(mouse_y, data->max.im, interpolation);
}

int		mouse_hook(int button, int x, int y, t_data *data)
{
	if (button != KEY_MOUSE_SCROLL_UP && button != KEY_MOUSE_SCROLL_DOWN)
		return (0);
	if (data->params->zoom == 1.1 && button == KEY_MOUSE_SCROLL_DOWN)
		return (1);
	if (x < data->mlx->image_width && y < data->mlx->image_height)
	{
		if (button == KEY_MOUSE_SCROLL_UP)
		{
			data->params->move.re = data->min.re +
			x * (data->max.re - data->min.re) / (data->mlx->image_width - 1.0);
			data->params->move.im = data->max.im -
			y * (data->max.im - data->min.im) / (data->mlx->image_height - 1.0);
			data->params->zoom += 0.0000001;
			data->params->zoom_factor = data->params->zoom;
		}
		if (button == KEY_MOUSE_SCROLL_DOWN)
		{
			data->params->zoom -= 0.00001;
			data->params->zoom_factor = 1.0 / data->params->zoom;
		}
		zoom(data, data->params->move.re,
				data->params->move.im, data->params->zoom_factor);
		mlx_destroy_image(data->mlx->p_mlx, data->mlx->img);
		expose_hook(data);
	}
	return (1);
}

int		julia_motion(int x, int y, t_data *data)
{
	if (data->type == julia && data->julia_mouse_lock == 0 &&
		x <= data->mlx->image_width && y <= data->mlx->image_height)
	{
		data->params->mouse.re = 4 * ((double)x / data->mlx->image_width - 0.5);
		data->params->mouse.im = 4 *
			((double)y / data->mlx->image_height - 0.5);
		set_complex(&(data->params->julia_k),
					data->params->mouse.re, data->params->mouse.im);
		mlx_destroy_image(data->mlx->p_mlx, data->mlx->img);
		expose_hook(data);
	}
	return (1);
}

void	move_image(t_data *data, int keycode)
{
	if (keycode == KEY_UP)
		{
			set_complex(&(data->min), data->min.re, data->min.im - 0.01);
			set_complex(&(data->max), data->max.re, data->max.im - 0.01);
		}
	if (keycode == KEY_DOWN)
		{
			set_complex(&(data->min), data->min.re, data->min.im + 0.01);
			set_complex(&(data->max), data->max.re, data->max.im + 0.01);
		}
	if (keycode == KEY_LEFT)
		{
			set_complex(&(data->min), data->min.re - 0.01, data->min.im);
			set_complex(&(data->max), data->max.re - 0.01, data->max.im);
		}
	if (keycode == KEY_RIGHT)
		{
			set_complex(&(data->min), data->min.re + 0.01, data->min.im);
			set_complex(&(data->max), data->max.re + 0.01, data->max.im);
		}
}

int		key_press(int keycode, t_data *data)
{
	if (keycode == KEY_ESC)
		exit(EXIT_SUCCESS);
	if (keycode == KEY_I)
		data->params->max_iter += 10;
	if (keycode == KEY_K)
		if (data->params->max_iter > 10)
			data->params->max_iter -= 10;
	if (keycode == KEY_M)
		data->julia_mouse_lock = (data->julia_mouse_lock == 0) ? 1 : 0;
	if (keycode == KEY_NUM_CLEAR && data->params->zoom != 1.1)
	{
		init_extremums(data);
		data->params->zoom = 1.1;
		data->params->zoom_factor = 0;
	}
	if (keycode == KEY_UP || keycode == KEY_DOWN
		|| keycode == KEY_LEFT || keycode == KEY_RIGHT)
		move_image(data, keycode);
	mlx_destroy_image(data->mlx->p_mlx, data->mlx->img);
	expose_hook(data);
	return (1);
}

int		close(int keycode)
{
	(void)keycode;
	exit(EXIT_SUCCESS);
}
