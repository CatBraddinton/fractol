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

#include "../inc/mandelbrot_and_julia.h"

static int	init_set(t_complex *n, double real, double imaginary, int mode)
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

static void	count_mandelbrot_set(t_data *data, t_mandelbrot *set)
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
			data->iter = 0;
			while (data->iter < data->max_iter
				&& init_set(&(set->pwr), set->z.r, set->z.im, MODE_BOOL))
			{
				set->temp = 2.0 * set->z.r * set->z.im + set->cmlx.im;
				init_set(&(set->z), (set->pwr.r - set->pwr.im + set->cmlx.r),
				set->temp, MODE_SET);
				data->iter++;
			}
			set_color_to_point(data, x, y);
		}
	}
}

void		draw_mandelbrot_set(t_data *data)
{
	t_mandelbrot	set;

	if ((data->img_buffer = mlx_get_data_addr(data->p_image, &(data->bpp),
	&(data->size_line), &(data->endian))) == NULL)
		error("Error: mlx failed to return information about created image\
		in draw_mandelbrot_set()");
	data->max_iter = 1500;
	init_set(&(set.min), -2.0, -2.0, MODE_SET);
	init_set(&(set.max), 2.0, 2.0, MODE_SET);
	init_set(&(set.factor),(set.max.r - set.min.r) / WIDTH,
				(set.max.im - set.min.im) / HEIGHT, MODE_SET);
	count_mandelbrot_set(data, &set);
}
