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
/*
void	*iterate_pixels(void *data)
{
	t_data *d;

	d = (t_data *)data;
	d->y = d->thread->y[d->thread->n][START];
	while (d->y < d->thread->y[d->thread->n][FINISH])
	{
		d->x = d->thread->x[d->thread->n][START];
		while (d->x < d->thread->x[d->thread->n][FINISH])
		{
			if (d->type == mandelbrot)
				draw_mandelbrot_set(d);
			else if (d->type == julia)
				draw_julia_set(d);
			d->x++;
		}
		d->y++;
	}
	return (data);
}

void	draw_fractals(t_data *data)
{
	int i;

	i = -1;
	while (++i < TOTAL_THREADS)
	{
		data->thread->n = i;
		pthread_create(&(data->thread->id[i]), NULL, iterate_pixels, data);
	}
	i = -1;
	while (++i < TOTAL_THREADS)
		pthread_join(data->thread->id[i], NULL);
}
*/
void	*iterate_pixels4(void *data)
{
	t_data *d;

	d = (t_data *)data;
	d->y[3] = d->mlx->image_height / 2;
	while (d->y[3] < d->mlx->image_height)
	{
		d->x[3] = d->mlx->image_width / 2;
		while (d->x[3] < d->mlx->image_width)
		{
			if (d->type == mandelbrot)
				draw_mandelbrot_set(d, d->x[3], d->y[3]);
			else if (d->type == julia)
				draw_julia_set(d, d->x[3], d->y[3]);
			d->x[3] += 1;
		}
		d->y[3] += 1;
	}
	pthread_exit(0);
}

void	*iterate_pixels3(void *data)
{
	t_data *d;

	d = (t_data *)data;
	d->y[2] = 0;
	while (d->y[2] < d->mlx->image_height / 2)
	{
		d->x[2] = d->mlx->image_width / 2;
		while (d->x[2] < d->mlx->image_width)
		{
			if (d->type == mandelbrot)
				draw_mandelbrot_set(d, d->x[2], d->y[2]);
			else if (d->type == julia)
				draw_julia_set(d, d->x[2], d->y[2]);
			d->x[2] += 1;
		}
		d->y[2] += 1;
	}
	pthread_exit(0);
}

void	*iterate_pixels2(void *data)
{
	t_data *d;

	d = (t_data *)data;
	d->y[1] = d->mlx->image_height / 2;
	while (d->y[1] < d->mlx->image_height)
	{
		d->x[1] = 0;
		while (d->x[1] < d->mlx->image_width / 2)
			{
				if (d->type == mandelbrot)
					draw_mandelbrot_set(d, d->x[1], d->y[1]);
				else if (d->type == julia)
					draw_julia_set(d, d->x[1], d->y[1]);
				d->x[1] += 1;
			}
			d->y[1] += 1;
	}
	pthread_exit(0);
}

void	*iterate_pixels1(void *data)
{
	t_data *d;

	d = (t_data *)data;
	d->y[0] = 0;
	while (d->y[0] < d->mlx->image_height / 2)
	{
		d->x[0] = 0;
		while (d->x[0] < d->mlx->image_width / 2)
		{
			if (d->type == mandelbrot)
				draw_mandelbrot_set(d, d->x[0], d->y[0]);
			else if (d->type == julia)
				draw_julia_set(d, d->x[0], d->y[0]);
			d->x[0]++;
		}
		d->y[0]++;
	}
	pthread_exit(0);
}

void	draw_fractals(t_data *data)
{
	pthread_t	id1;
	pthread_t	id2;
	pthread_t	id3;
	pthread_t	id4;

	pthread_create(&id1, NULL, &iterate_pixels1, data);
	pthread_create(&id2, NULL, &iterate_pixels2, data);
	pthread_create(&id3, NULL, &iterate_pixels3, data);
	pthread_create(&id4, NULL, &iterate_pixels4, data);
	pthread_join(id1, NULL);
	pthread_join(id2, NULL);
	pthread_join(id3, NULL);
	pthread_join(id4, NULL);

}

static int	get_fractal_type(char *input)
{
	int len;

	len = ft_strlen(input);
	if (len == 5 && ft_strnequ(input, "julia", len))
		return (julia);
	if (len == 10 && ft_strnequ(input, "mandelbrot", len))
		return (mandelbrot);
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

void	init_mlx_window(t_data *data, char *name)
{
	if ((data->mlx->p_mlx = mlx_init()) == NULL)
		error(strerror(errno));
	if (!(data->mlx->win = mlx_new_window(data->mlx->p_mlx, WIN_W, WIN_H, name)))
		error(strerror(errno));
	mlx_expose_hook(data->mlx->win, expose_hook, data);
	mlx_hook(data->mlx->win, 2, 0, key_press, data);
	mlx_hook(data->mlx->win, 6, 0, julia_motion, data);
	mlx_hook(data->mlx->win, 17, 0, close, data);
	mlx_mouse_hook(data->mlx->win, mouse_hook, data);
	mlx_do_key_autorepeaton(data->mlx->p_mlx);
	mlx_loop(data->mlx->p_mlx);
}

void		draw_fractal_image(char *name)
{
	t_data 		*data;

	if ((data = (t_data *)malloc(sizeof(t_data))) == NULL)
		error(strerror(errno));
	data->type = get_fractal_type(name);
	if (data->type == invalid)
		error("fractal type value is invalid");
	init_programm_architecture(data);
	if (data->type == mandelbrot)
	{
		set_complex(&(data->min), -2.0, -1.0);
		set_complex(&(data->max), 1.0, 1.0);
	}
	else if (data->type == julia)
	{
		set_complex(&(data->min), -3.00, -3.00);
		set_complex(&(data->max), 3.00,  3.00);
	}
	init_mlx_window(data, name);
}
