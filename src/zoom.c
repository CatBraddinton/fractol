/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdudko <kdudko@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 23:35:20 by kdudko            #+#    #+#             */
/*   Updated: 2019/09/27 23:35:21 by kdudko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

void	zoom(t_data *data, double mouse_x, double mouse_y, double zoom_factor)
{
	double interpolation;

	interpolation = 1.0 / zoom_factor;
	data->min.re = interpolate(mouse_x, data->min.re, interpolation);
	data->min.im = interpolate(mouse_y, data->min.im, interpolation);
	data->max.re = interpolate(mouse_x, data->max.re, interpolation);
	data->max.im = interpolate(mouse_y, data->max.im, interpolation);
}

void	zoom_image(int button, int x, int y, t_data *data)
{
	if (button == KEY_MOUSE_SCROLL_UP)
	{
		data->params->move.re = data->min.re +
		x * (data->max.re - data->min.re) / (IMG_W - 1.0);
		data->params->move.im = data->max.im -
		y * (data->max.im - data->min.im) / (IMG_H - 1.0);
		data->params->zoom += 0.0001;
		data->params->zoom_factor = data->params->zoom;
	}
	if (button == KEY_MOUSE_SCROLL_DOWN)
	{
		data->params->zoom -= 0.0001;
		data->params->zoom_factor = 1.0 / data->params->zoom;
	}
	zoom(data, data->params->move.re,
			data->params->move.im, data->params->zoom_factor);
	mlx_destroy_image(data->mlx->p_mlx, data->mlx->img);
	expose_hook(data);
}
