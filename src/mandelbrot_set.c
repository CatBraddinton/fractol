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

int		get_color_value(int iter, int max, int col1, int col2)
{
	t_color	color;
	double	percent;

	percent = (double)iter / (double)max;
	if (iter <= max / 2 - 1)
	{
		color.r = (int)(0x36 * (1 - percent) * pow(percent, 3) * 255);
		color.g = (int)(0x25 * pow((1 - percent), 3) * pow(percent, 2) * 255);
		color.b = (int)(0x14 * pow((1 - percent), 3) * percent * 255);
	}
	else if ((iter >= max / 2) && (iter < max))
	{
		color.r = get_light((col1 >> 16) & 0xFF, (col2 >> 16) & 0xFF, percent);
		color.g = get_light((col1 >> 8) & 0xFF, (col2 >> 8) & 0xFF, percent);
		color.b = get_light(col1 & 0xFF, col2 & 0xFF, percent);
	}
	else if (iter == max)
		return (BLACK);
	return ((color.r << 16) | (color.g << 8) | color.b);
}

void	set_color_to_point(t_data *data, t_mandelbrot *set, int x, int y)
{
	int	i;
	int	color;

	color = get_color_value(set->iter, set->max_iter, SET8, SET88);
	x = (x > 0) ? x * data->cam.zoom : -x * data->cam.zoom;
	y = (y > 0) ? y * data->cam.zoom : -y * data->cam.zoom;
	if (x < IMG_WIDTH && y < IMG_HEIGHT)
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

void	init_set_data(t_mandelbrot *set)
{
	double temp;

	set->max_iter = 50;
	init_set(&(set->min), -2.0, -2.0, MODE_SET);
	temp = set->min.im + (set->max.r - set->min.r) * IMG_WIDTH / IMG_HEIGHT;
	init_set(&(set->max), 2.0, temp, MODE_SET);
	init_set(&(set->factor),
				((set->max.r - set->min.r) / (IMG_WIDTH - 1)),
				((set->max.im - set->min.im) / (IMG_HEIGHT - 1)), MODE_SET);
}

void	count_mandelbrot_set(t_data *data, t_mandelbrot *set)
{
	int x;
	int y;

	y = -1;
	while (++y < IMG_HEIGHT)
	{
		set->cmlx.im = set->max.im - y * set->factor.im;
		x = -1;
		while (++x < IMG_WIDTH)
		{
			set->cmlx.r = set->min.r + x * set->factor.r;
			init_set(&(set->z), set->cmlx.r, set->cmlx.im, MODE_SET);
			set->iter = 0;
			while (set->iter < set->max_iter)
			{
				if (!(init_set(&(set->pwr), set->z.r, set->z.im, MODE_BOOL)))
					break;
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

	init_cam(data);
	if (!(data->p_image = mlx_new_image(data->p_mlx, IMG_WIDTH, IMG_HEIGHT)))
		error("Error: mlx failed to create new image in draw_mandelbrot_set()");
	if ((data->img_buffer = mlx_get_data_addr(data->p_image, &(data->bpp),
	&(data->size_line), &(data->endian))) == NULL)
		error("Error: mlx failed to return information about created image\
		in draw_mandelbrot_set()");
	init_set_data(&set);
	count_mandelbrot_set(data, &set);
	mlx_put_image_to_window(data->p_mlx, data->p_window, data->p_image,	0, 0);
}
