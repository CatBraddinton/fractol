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

void	colorize_point(t_data *data, t_mandelbrot *values, int x, int y)
{
	double	temp;
	int 	i;

	temp = (double)values->iter / (double)values->max_iter;
	data->p_color.red = (int)(9 * (1 - temp) * pow(temp, 3) * 255);
	data->p_color.green = (int)(15 * pow((1 - temp), 2) * pow(temp, 2) * 255);
	data->p_color.blue = (int)(8.5 * pow((1 - temp), 3) * temp * 255);
	if ((x >= 0 && x < data->img_width) && (y >= 0 && y < data->img_height))
	{
		i = (x * data->mlx_data->bpp / 8) + (y * data->mlx_data->size_line);
		data->mlx_data->img_buffer[i] = data->p_color.red;
		data->mlx_data->img_buffer[++i] = data->p_color.green;
		data->mlx_data->img_buffer[++i] = data->p_color.blue;
		data->mlx_data->img_buffer[++i] = 0;
	}
}

void	init_complex(t_complex *n, double real, double imaginary)
{
	n->real = real;
	n->im = imaginary;
}

void	init_values(t_mandelbrot *values, int h, int w)
{
	double temp;

	values->max_iter = 50;
	init_complex(&(values->min), -2.0, -2.0);
	temp = values->min.im + (values->max.real - values->min.real)
						* h / w;
	init_complex(&(values->max), 2.0, temp);
	init_complex(&(values->factor),
				((values->max.real - values->min.real) / (w - 1)),
				((values->max.im - values->min.im) / (h - 1)));
}

void	count_mandelbrot_set(t_data *data, t_mandelbrot *values)
{
	int x;
	int y;

	init_values(values, data->img_height, data->img_width);
	y = -1;
	while (++y < data->img_height)
	{
		values->center.im = values->max.im - y * values->factor.im;
		x = -1;
		while (++x < data->img_width)
		{
			values->center.real = values->min.real + x * values->factor.real;
			init_complex(&(values->z), values->center.real, values->center.im);
			values->iter = 0;
			while ((pow(values->z.real, 2.0) + pow(values->z.im, 2.0)) <= 4
            && values->iter < values->max_iter)
			{
				init_complex(&(values->z), (pow(values->z.real, 2.0) -
				pow(values->z.im, 2.0) + values->center.real),
			  	(2.0 * values->z.real * values->z.im + values->center.im));
				values->iter++;
				printf("%f, %f\n", values->z.real, values->z.im);
			}
			colorize_point(data, values, x, y);
		}
	}
}

void	draw_mandelbrot_set(t_data *data)
{
	t_mandelbrot	*values;

	if ((values = (t_mandelbrot *)malloc(sizeof(t_mandelbrot))) == NULL)
		error("Error: malloc failed in draw_mandelbrot_set()");
	if ((data->mlx_data->p_mlx = mlx_init()) == NULL)
		error("Error: mlx init failed in draw_mandelbrot_set()");
	if (!(data->mlx_data->p_window = mlx_new_window(data->mlx_data->p_mlx,
		data->win_width, data->win_height,
		"Mandelbrot Set")))
		error("Error: mlx failed to open new window in draw_mandelbrot_set()");
	if (!(data->mlx_data->p_image = mlx_new_image(data->mlx_data->p_mlx,
		data->img_width, data->img_height)))
		error("Error: mlx failed to create new image in draw_mandelbrot_set()");
	if ((data->mlx_data->img_buffer = mlx_get_data_addr(data->mlx_data->p_image,
		&(data->mlx_data->bpp), &(data->mlx_data->size_line),
		&(data->mlx_data->endian))) == NULL)
		error("Error: mlx failed to return information about created image\
		in draw_mandelbrot_set()");
	count_mandelbrot_set(data, values);
	mlx_hook(data->mlx_data->p_window, 2, 0, key_press, &data);
	mlx_hook(data->mlx_data->p_window, 17, 0, close, &data);
	mlx_loop(data->mlx_data->p_mlx);
}
