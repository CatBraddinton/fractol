/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia_set.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdudko <kdudko@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 12:06:10 by kdudko            #+#    #+#             */
/*   Updated: 2019/09/07 12:06:13 by kdudko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/julia.h"

static int	get_color_value(int iter, int max_iter)
{
	t_color	color;
	double	percent;

	if (iter == max_iter)
		return (BLACK);
	percent = (double)iter / (double)max_iter;
	color.r = (int)(9 * (1 - percent) * pow(percent, 3) * 255);
	color.g = (int)(20 * pow((1 - percent), 2) * pow(percent, 2) * 255);
	color.b = (int)(8.5 * pow((1 - percent), 3) * percent * 255);
	return ((color.r << 16) | (color.g << 8) | color.b);
}

void	color_point(t_data *data, int **buff)
{
	int	x;
	int	y;
	int	color;
	int i;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			color = get_color_value(buff[y][x], data->params->max_iter);
			i = (x * data->mlx->bpp / 8) + (y * data->mlx->size);
			data->mlx->img_buffer[i] = color;
			data->mlx->img_buffer[++i] = color >> 8;
			data->mlx->img_buffer[++i] = color >> 16;
			data->mlx->img_buffer[++i] = 0;
			x++;
		}
		y++;
	}
}

void	draw_julia_set(t_data *data)
{
	int		**buff;
	t_set	set;
	int 	y;
	int 	x;

	buff = (int **)malloc(HEIGHT * sizeof(int *));
	init_complex(&(set.k), -0.7, 0.27015);
	y = 0;
	while (y < HEIGHT)
	{
		buff[y] = (int *)malloc(WIDTH * sizeof(int));
		x = 0;
		while (x < WIDTH)
		{
			set.new_z.re = 1.5 * (x - WIDTH / 2) / (0.5 * data->params->zoom
				* WIDTH) + data->params->move_x;
			set.new_z.im = (y - HEIGHT / 2) / (0.5 * data->params->zoom
					* HEIGHT) + data->params->move_y;
			data->params->iter = 0;
			while (data->params->iter < data->params->max_iter)
			{
				init_complex(&(set.old_z), set.new_z.re, set.new_z.im);
				set.new_z.re = set.old_z.re * set.old_z.re -
					set.old_z.im * set.old_z.im + set.k.re;
				set.new_z.im = 2 * set.old_z.re * set.old_z.im + set.k.im;
				data->params->iter++;
				if ((set.new_z.re * set.new_z.re + set.new_z.im * set.new_z.im)
					> 4)
					break ;
			}
			buff[y][x] = data->params->iter;
			x++;
		}
		y++;
	}
	data->mlx->p_img = mlx_new_image(data->mlx->p_mlx, WIDTH, HEIGHT);
	data->mlx->img_buffer = mlx_get_data_addr(data->mlx->p_img,
		&(data->mlx->bpp), &(data->mlx->size), &(data->mlx->end));
	color_point(data, buff);
	mlx_put_image_to_window(data->mlx->p_mlx, data->mlx->p_win,
			data->mlx->p_img, 0, 0);
}
