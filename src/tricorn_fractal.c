/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tricorn_fractal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdudko <kdudko@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 23:19:35 by kdudko            #+#    #+#             */
/*   Updated: 2019/09/27 23:19:36 by kdudko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

void	draw_tricorn_fractal(t_data *data, int x, int y, int i)
{
	t_set set;

	set.f.re = (data->max.re - data->min.re) / (data->mlx->image_width - 1.0);
	set.f.im = (data->max.im - data->min.im) / (data->mlx->image_height - 1.0);
	set.c.re = data->min.re + x * set.f.re;
	set.c.im = data->max.im - y * set.f.im;
	set_complex(&(set.new_z), set.c.re, set.c.im);
	count_points(data, &set);
	data->iter[i] = set.iter;
	color_point(data, x, y, i);
}
