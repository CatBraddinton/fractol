/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot_set.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdudko <kdudko@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 20:18:55 by kdudko            #+#    #+#             */
/*   Updated: 2019/08/14 20:18:58 by kdudko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/mandelbrot_set.h"

int		get_light(int start, int end, double percentage)
{
	return ((int)((1 - percentage) * start * percentage * end));
}

int		get_color_value(int iter, int max)
{
	t_color	color;
	double	percent;

	if (iter == max)
		return (BLACK);
	percent = (double)iter / (double)max;
	color.r = (int)(9 * (1 - percent) * pow(percent, 3) * 255 + 130);
	color.g = (int)(15 * pow((1 - percent), 2) * pow(percent, 2) * 255 + 100);
	color.b = (int)(8.5 * pow((1 - percent), 3) * percent * 255 + 100);
	return ((color.r << 16) | (color.g << 8) | color.b);
}

void	set_color_to_point(t_data *data, t_mandelbrot *set, int x, int y)
{
	int	i;
	int	color;

	color = get_color_value(set->iter, set->max_iter);
	x = (x > 0) ? x : -x;
	y = (y > 0) ? y : -y;
	if (x < WIDTH && y < HEIGHT)
	{
		i = (x * data->bpp / 8) + (y * data->size_line);
		data->img_buffer[i] = color;
		data->img_buffer[++i] = color >> 8;
		data->img_buffer[++i] = color >> 16;
		data->img_buffer[++i] = 0;
	}
}

int		init_set(t_complex *n, double real, double imaginary, int mode)
{
	if (mode == MODE_SET)
	{
		n->r = real;
		n->im = imaginary;
	}
	else if (mode == MODE_POW)
	{
		n->r = pow(real, POWER);
		n->im = pow(imaginary, POWER);
	}
	else if (mode == MODE_BOOL)
	{
		n->r = pow(real, POWER);
		n->im = pow(imaginary, POWER);
		if (n->r + n->im <= 4.0)
			return (1);
	}
	return (0);
}

void	count_mandelbrot_set(t_data *data, t_mandelbrot *set)
{
	int x;
	int y;

	y = -1;
	while (++y < HEIGHT)
	{
		set->cmlx.im = set->max.im - y * set->factor.im;
		x = -1;
		while (++x < WIDTH)
		{
			set->cmlx.r = set->min.r + x * set->factor.r;
			init_set(&(set->z), 0, 0, MODE_SET);
			set->iter = 0;
			while (set->iter < set->max_iter
				&& init_set(&(set->pwr), set->z.r, set->z.im, MODE_BOOL))
			{
				set->temp = 2.0 * set->z.r * set->z.im + set->cmlx.im;
				init_set(&(set->z), (set->pwr.r - set->pwr.im + set->cmlx.r),
				set->temp, MODE_SET);
				set->iter++;
			}
			set_color_to_point(data, set, x, y);
		}
	}
}

void	draw_mandelbrot_set(t_data *data)
{
	t_mandelbrot	set;

	if ((data->img_buffer = mlx_get_data_addr(data->p_image, &(data->bpp),
	&(data->size_line), &(data->endian))) == NULL)
		error("Error: mlx failed to return information about created image\
		in draw_mandelbrot_set()");
	set.max_iter = 1500;
	init_set(&(set.min), -2.0, -2.0, MODE_SET);
	init_set(&(set.max), 2.0, 2.0, MODE_SET);
	init_set(&(set.factor),(set.max.r - set.min.r) / WIDTH,
				(set.max.im - set.min.im) / HEIGHT, MODE_SET);
	count_mandelbrot_set(data, &set);
}
