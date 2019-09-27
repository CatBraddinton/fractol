/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burning_ship_fractal.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdudko <kdudko@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 21:42:30 by kdudko            #+#    #+#             */
/*   Updated: 2019/09/27 21:42:32 by kdudko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

void	draw_burning_ship_fractal(t_data *data, int x, int y, int i)
{
	t_set set;

	set.f.re = (data->max.re - data->min.re) / (data->mlx->image_width - 1.0);
	set.f.im = (data->max.im - data->min.im) / (data->mlx->image_height - 1.0);
	set.c.re = data->min.re + x * set.f.re;
	set.c.im = data->max.im - y * set.f.im;
	set_complex(&(set.new_z), 0.0, 0.0);
	count_points(data, &set);
	data->iter[i] = set.iter;
	color_point(data, x, y, i);
}
