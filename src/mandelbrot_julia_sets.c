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

int			is_in_mandelbrot_set(double x, double y)
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

static void	count_points(t_data *data, t_set *set)
{
	double temp;

	set->iter = 0;
	set_complex(&(set->z_sqrt),
		set->new_z.re * set->new_z.re, set->new_z.im * set->new_z.im);
	if (data->type == mandelbrot && is_in_mandelbrot_set(set->c.re, set->c.im))
		set->iter = data->params->max_iter;
	else
		while (set->iter < data->params->max_iter)
		{
			set_complex(&(set->old_z), set->new_z.re, set->new_z.im);
			temp = set->z_sqrt.re - set->z_sqrt.im;
			set->new_z.re = temp + set->c.re;
			temp = set->old_z.re + set->old_z.re;
			temp = (data->type == tricorn) ? -temp : temp;
			set->new_z.im = temp * set->old_z.im + set->c.im;
			set->iter++;
			set_complex(&(set->z_sqrt),
				set->new_z.re * set->new_z.re, set->new_z.im * set->new_z.im);
			temp = set->z_sqrt.re + set->z_sqrt.im;
			if (temp > 4)
				break ;
		}
}

void		draw_julia_set(t_data *data, int x, int y)
{
	t_set set;

	set.new_z.re = data->min.re + x /
		(data->mlx->image_width - 1.0) * (data->max.re - data->min.re);
	set.new_z.im = data->max.im - y /
		(data->mlx->image_height - 1.0) * (data->max.im - data->min.im);
	set.c.re = data->params->julia_k.re;
	set.c.im = data->params->julia_k.im;
	count_points(data, &set);
	data->iter = set.iter;
	color_point(data, x, y);
}

void		draw_mandelbrot_set(t_data *data, int x, int y)
{
	t_set set;

	set.f.re = (data->max.re - data->min.re) / (data->mlx->image_width - 1.0);
	set.f.im = (data->max.im - data->min.im) / (data->mlx->image_height - 1.0);
	set.c.re = data->min.re + x * set.f.re;
	set.c.im = data->max.im - y * set.f.im;
	set_complex(&(set.new_z), 0.0, 0.0);
	count_points(data, &set);
	data->iter = set.iter;
	color_point(data, x, y);
}

void		draw_tricorn_fractal(t_data *data, int x, int y)
{
	t_set set;

	set.f.re = (data->max.re - data->min.re) / (data->mlx->image_width - 1.0);
	set.f.im = (data->max.im - data->min.im) / (data->mlx->image_height - 1.0);
	set.c.re = data->min.re + x * set.f.re;
	set.c.im = data->max.im - y * set.f.im;
	set_complex(&(set.new_z), set.c.re, set.c.im);
	count_points(data, &set);
	data->iter = set.iter;
	color_point(data, x, y);
}
