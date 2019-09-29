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

void		define_call_function(t_data *d, int i)
{
	if (d->type == mandelbrot)
		draw_mandelbrot_set(d, d->x[i], d->y[i], i);
	else if (d->type == julia)
		draw_julia_set(d, d->x[i], d->y[i], i);
	else if (d->type == tricorn)
		draw_tricorn_fractal(d, d->x[i], d->y[i], i);
	else if (d->type == burning_ship)
		draw_burning_ship_fractal(d, d->x[i], d->y[i], i);
}

void		*iterate_pixels(void *data)
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
		while (d->x[i] < IMG_W)
		{
			define_call_function(d, i);
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

static int	get_fractal_type(char *input)
{
	int len;

	len = (int)ft_strlen(input);
	if (len == 5 && ft_strnequ(input, "julia", len))
		return (julia);
	if (len == 10 && ft_strnequ(input, "mandelbrot", len))
		return (mandelbrot);
	if (len == 7 && ft_strnequ(input, "tricorn", len))
		return (tricorn);
	if (len == 12 && ft_strnequ(input, "burning_ship", len))
		return (burning_ship);
	return (-1);
}

void		draw_fractal_image(char *name)
{
	t_data *data;

	if ((data = (t_data *)malloc(sizeof(t_data))) == NULL)
		error(MALLOK_ERROR);
	data->type = get_fractal_type(name);
	if (data->type == invalid)
		error(TYPE_ERROR);
	init_programm_architecture(data);
	init_extremums(data);
	if ((data->mlx->p_mlx = mlx_init()) == NULL)
		error(MLX_ERROR);
	data->mlx->win = mlx_new_window(data->mlx->p_mlx, data->mlx->win_w,
													data->mlx->win_h, name);
	if (!(data->mlx->win))
		error(MLX_ERROR);
	create_image(data);
}
