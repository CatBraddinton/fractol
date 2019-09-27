/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia_set.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdudko <kdudko@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 23:19:20 by kdudko            #+#    #+#             */
/*   Updated: 2019/09/27 23:19:22 by kdudko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

void	draw_julia_set(t_data *data, int x, int y, int i)
{
	t_set set;

	set.new_z.re = data->min.re + x /
		(data->mlx->image_width - 1.0) * (data->max.re - data->min.re);
	set.new_z.im = data->max.im - y /
		(data->mlx->image_height - 1.0) * (data->max.im - data->min.im);
	set.c.re = data->params->julia_k.re;
	set.c.im = data->params->julia_k.im;
	count_points(data, &set);
	data->iter[i] = set.iter;
	color_point(data, x, y, i);
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
