/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot_set.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdudko <kdudko@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 12:05:29 by kdudko            #+#    #+#             */
/*   Updated: 2019/09/07 12:05:33 by kdudko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

void	draw_mandelbrot_set(t_data *data)
{
	t_set	set;
	int 	y;
	int 	x;

	data->buff = (int **)malloc(HEIGHT * sizeof(int *));
	init_complex(&(set.k), -0.7, 0.27015);
	y = 0;
	while (y < HEIGHT)
	{
		data->buff[y] = (int *)malloc(WIDTH * sizeof(int));
		set.k.im = 2.0 * ((double)y - HEIGHT / 2) / (0.5 * data->params->zoom
				* HEIGHT) + data->params->move_y;
		x = 0;
		while (x < WIDTH)
		{
			set.k.re = 2.0 * ((double)x - WIDTH / 2) /
			(0.5 * data->params->zoom * WIDTH) + data->params->move_x;
			init_complex(&(set.new_z), 0.0, 0.0);
			data->params->iter = 0;
			while (data->params->iter < data->params->max_iter)
			{
				init_complex(&(set.old_z), set.new_z.re, set.new_z.im);
				set.new_z.re = set.old_z.re * set.old_z.re -
					set.old_z.im * set.old_z.im + set.k.re;
				set.new_z.im = 2.0 * set.old_z.re * set.old_z.im + set.k.im;
				data->params->iter++;
				if ((pow(set.new_z.re , 2.0) + pow(set.new_z.im, 2.0))
					> 4)
					break ;
			}
			data->buff[y][x] = data->params->iter;
			x++;
		}
		y++;
	}
	data->mlx->p_img = mlx_new_image(data->mlx->p_mlx, WIDTH, HEIGHT);
	data->mlx->img_buffer = mlx_get_data_addr(data->mlx->p_img,
		&(data->mlx->bpp), &(data->mlx->size), &(data->mlx->end));
	color_point(data,data->buff);
	free_buff(data->buff);
	mlx_put_image_to_window(data->mlx->p_mlx, data->mlx->p_win,
			data->mlx->p_img, 0, 0);
}
