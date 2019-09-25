/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdudko <kdudko@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 17:45:40 by kdudko            #+#    #+#             */
/*   Updated: 2019/09/17 17:45:42 by kdudko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

void		*iterate_pixels(void *data)
{
	t_data	*d;
	int		i;
	int		step;
	int		last;

	d = (t_data *)data;
	i = d->i;
	pthread_mutex_unlock(&(d->lock));
	step = d->mlx->image_height / TOTAL_THREADS;
	last = (i == TOTAL_THREADS - 1) ? d->mlx->image_height : step * (i + 1);
	d->y[i] = 0;
	while (d->y[i] < last)
	{
		d->x[i] = 0;
		while (d->x[i] < d->mlx->image_width)
		{
			if (d->type == mandelbrot)
				draw_mandelbrot_set(d, d->x[i], d->y[i]);
			else if (d->type == julia)
				draw_julia_set(d, d->x[i], d->y[i]);
			else if (d->type == tricorn)
				draw_tricorn_fractal(d, d->x[i], d->y[i]);
			d->x[i]++;
		}
		d->y[i]++;
	}
	pthread_exit(0);
}

void		draw_fractals(t_data *data)
{
	int		i;

	pthread_mutex_init(&(data->lock), NULL);
	i = -1;
	while (++i < TOTAL_THREADS)
	{
		pthread_mutex_lock(&(data->lock));
		data->i = i;
		pthread_create(&(data->id[i]), NULL, &iterate_pixels, data);
	}
	i = -1;
	while (++i < TOTAL_THREADS)
		pthread_join(data->id[i], NULL);
	pthread_mutex_destroy(&(data->lock));
}

static int	get_fractal_type(char *input)
{
	int len;

	len = ft_strlen(input);
	if (len == 5 && ft_strnequ(input, "julia", len))
		return (julia);
	if (len == 10 && ft_strnequ(input, "mandelbrot", len))
		return (mandelbrot);
	if (len == 7 && ft_strnequ(input, "tricorn", len))
		return (tricorn);
	return (-1);
}

int			expose_hook(t_data *data)
{
	data->mlx->img = mlx_new_image(data->mlx->p_mlx, data->mlx->image_width,
		data->mlx->image_height);
	data->mlx->image = mlx_get_data_addr(data->mlx->img,
		&(data->mlx->bpp), &(data->mlx->size), &(data->mlx->end));
	draw_fractals(data);
	mlx_put_image_to_window(data->mlx->p_mlx, data->mlx->win,
		data->mlx->img, 0, 0);
	return (0);
}

void		draw_fractal_image(char *name)
{
	t_data *data;

	if ((data = (t_data *)malloc(sizeof(t_data))) == NULL)
		error(strerror(errno));
	data->type = get_fractal_type(name);
	if (data->type == invalid)
		error("fractal type value is invalid");
	init_programm_architecture(data);
	if (data->type == julia)
	{
		set_complex(&(data->min), -3.00, -3.00);
		set_complex(&(data->max), 3.00, 3.00);
	}
	else
	{
		set_complex(&(data->min), -2.5, -1.0);
		set_complex(&(data->max), 1.0, 1.0);
	}
	init_mlx_window(data, name);
}
