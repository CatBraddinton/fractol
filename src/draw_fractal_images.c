/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_fractal_images.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdudko <kdudko@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/02 14:32:40 by kdudko            #+#    #+#             */
/*   Updated: 2019/10/02 14:32:42 by kdudko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

int			julia_motion(int x, int y, t_data *data)
{
	if (data->type == julia && data->julia_mouse_lock == 0 &&
		x <= data->mlx->im_w && y <= IMG_H)
	{
		data->params->mouse.re = 4 * ((double)x / data->mlx->im_w - 0.5);
		data->params->mouse.im = 4 * ((double)y / IMG_H - 0.5);
		set_complex(&(data->params->julia_k),
					data->params->mouse.re, data->params->mouse.im);
		mlx_destroy_image(data->mlx->p_mlx, data->mlx->img);
		expose_hook(data);
	}
	return (1);
}

static void	draw_julia_set(t_data *data, int x, int y, int i)
{
	t_set set;

	set.new_z.re = data->min.re + x /
		(data->mlx->im_w - 1.0) * (data->max.re - data->min.re);
	set.new_z.im = data->max.im - y /
		(IMG_H - 1.0) * (data->max.im - data->min.im);
	set.c.re = data->params->julia_k.re;
	set.c.im = data->params->julia_k.im;
	count_points(data, &set);
	data->iter[i] = set.iter;
	color_point(data, x, y, i);
}

static void	init_fractal(t_data *data, int x, int y, int i)
{
	t_set set;

	set.f.re = (data->max.re - data->min.re) / (data->mlx->im_w - 1.0);
	set.f.im = (data->max.im - data->min.im) / (IMG_H - 1.0);
	set.c.re = data->min.re + x * set.f.re;
	set.c.im = data->max.im - y * set.f.im;
	if (data->type == tricorn)
		set_complex(&(set.new_z), set.c.re, set.c.im);
	else
		set_complex(&(set.new_z), 0.0, 0.0);
	if (data->type == mandelbrot && is_in_mandelbrot_set(set.c.re, set.c.im))
		set.iter = data->params->max_iter;
	else
		count_points(data, &set);
	data->iter[i] = set.iter;
	color_point(data, x, y, i);
}

static void	*iterate_pixels(void *data)
{
	t_data	*d;
	int		i;
	int		step;
	int		last;

	d = (t_data *)data;
	i = d->i;
	pthread_mutex_unlock(&(d->lock));
	step = IMG_H / TOTAL_THREADS;
	last = (i == TOTAL_THREADS - 1) ? IMG_H : step * (i + 1);
	d->y[i] = 0;
	while (d->y[i] < last)
	{
		d->x[i] = 0;
		while (d->x[i] < d->mlx->im_w)
		{
			if (d->type == julia)
				draw_julia_set(d, d->x[i], d->y[i], i);
			else
				init_fractal(d, d->x[i], d->y[i], i);
			d->x[i]++;
		}
		d->y[i]++;
	}
	pthread_exit(0);
}

void		draw_fractals(t_data *data)
{
	pthread_t	id[TOTAL_THREADS];
	int			i;

	pthread_mutex_init(&(data->lock), NULL);
	i = -1;
	while (++i < TOTAL_THREADS)
	{
		pthread_mutex_lock(&(data->lock));
		data->i = i;
		pthread_create(&(id[i]), NULL, &iterate_pixels, data);
	}
	i = -1;
	while (++i < TOTAL_THREADS)
		pthread_join(id[i], NULL);
	pthread_mutex_destroy(&(data->lock));
}
