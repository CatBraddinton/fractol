/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot_julia_sets.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdudko <kdudko@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 14:01:23 by kdudko            #+#    #+#             */
/*   Updated: 2019/09/08 14:01:25 by kdudko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

void	count_points(t_data *data, t_cnum complex)
{
	double temp;

	data->params->iter = 0;
	while (data->params->iter < data->params->max_iter)
	{
		set_complex(&(data->set.old_z), data->set.new_z.re, data->set.new_z.im);
		temp = data->set.z_sqrt.re - data->set.z_sqrt.im;
		data->set.new_z.re = temp + complex.re;
		temp = data->set.old_z.re + data->set.old_z.re;
		data->set.new_z.im = temp * data->set.old_z.im + complex.im;
		data->params->iter++;
		set_complex(&(data->set.z_sqrt),
			pow(data->set.new_z.re, 2.0), pow(data->set.new_z.im, 2.0));
		temp = data->set.z_sqrt.re + data->set.z_sqrt.im;
		if (temp > 4)
			break ;
	}
}

void	draw_julia_set(t_data *data)
{
	int			y;
	int			x;
	pthread_t	id;
	
	init_buffer(data);
	y = -1;
	while (++y < HEIGHT && (x = -1))
		while (++x < WIDTH)
		{
			data->set.new_z.re = data->re_min + (double)x * data->set.delta.re;
			data->set.new_z.im = data->im_min + (double)y * data->set.delta.im;
			set_complex(&(data->set.z_sqrt),
				pow(data->set.new_z.re, 2.0), pow(data->set.new_z.im, 2.0));
			count_points(data, data->set.k);
			data->buff[y][x] = data->params->iter;
		}
	color_point(data, data->buff);
	free_buff(data->buff);
}

void	draw_mandelbrot_set(t_data *data)
{
	int y;
	int x;

	init_buffer(data);
	y = -1;
	while (++y < HEIGHT && (x = -1))
	{
		while (++x < WIDTH)
		{
			data->set.c.re = data->re_min + (double)x * data->set.delta.re;
			data->set.c.im = data->im_min + (double)y * data->set.delta.im;
			set_complex(&(data->set.new_z), 0.0, 0.0);
			set_complex(&(data->set.z_sqrt),
				pow(data->set.new_z.re, 2.0), pow(data->set.new_z.im, 2.0));
			count_points(data, data->set.c);
			data->buff[y][x] = data->params->iter;
		}
	}
	color_point(data, data->buff);
	free_buff(data->buff);
}
