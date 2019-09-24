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

int		is_in_mandelbrot_set(double x, double y)
{
	double sqrt_x;
	double sqrt_y;
	double z;
	double q;
	double temp;

	temp = (x - 1.0 / 4.0);
	sqrt_x = temp * temp;
	sqrt_y = y * y;
	q = sqrt_x + sqrt_y;
	z = q * (q + temp);
	temp = sqrt_y / 4.0;
	if (z <= temp)
		return (1);
	return (0);
}

void		count_points(t_data *data)
{
	double temp;

	data->params->iter = 0;
	set_complex(&(data->set->z_sqrt),
		pow(data->set->new_z.re, 2.0), pow(data->set->new_z.im, 2.0));
	if (data->type == 2 && is_in_mandelbrot_set(data->set->c.re, data->set->c.im))
		data->params->iter = data->params->max_iter;
	else
		while (data->params->iter < data->params->max_iter)
		{
			set_complex(&(data->set->old_z), data->set->new_z.re, data->set->new_z.im);
			temp = data->set->z_sqrt.re - data->set->z_sqrt.im;
			data->set->new_z.re = temp + data->set->c.re;
			temp = data->set->old_z.re + data->set->old_z.re;
			data->set->new_z.im = temp * data->set->old_z.im + data->set->c.im;
			data->params->iter++;
			set_complex(&(data->set->z_sqrt),
				pow(data->set->new_z.re, 2.0), pow(data->set->new_z.im, 2.0));
				temp = data->set->z_sqrt.re + data->set->z_sqrt.im;
				if (temp > 4)
				break ;
			}
}

void	draw_julia_set(t_data *data)
{
	data->set->new_z.re = data->min.re + data->x /
		(data->mlx->image_width - 1.0) * (data->max.re - data->min.re);
	data->set->new_z.im = data->max.im - data->y /
		(data->mlx->image_height - 1.0) * (data->max.im - data->min.im);
	data->set->c.re = data->set->k.re;
	data->set->c.im = data->set->k.im;
	count_points(data);
	color_point(data);
}

void	draw_mandelbrot_set(t_data *data)
{
	set_complex(&(data->set->factor),
		((data->max.re - data->min.re) / (data->mlx->image_width - 1.0)),
		((data->max.im - data->min.im) / (data->mlx->image_height - 1.0)));
	data->set->c.re = data->min.re + data->x * data->set->factor.re;
	data->set->c.im = data->max.im - data->y * data->set->factor.im;
	set_complex(&(data->set->new_z), 0.0, 0.0);
	count_points(data);
	// histogram_coloring(data, data->buff);
	color_point(data);
}
