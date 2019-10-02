/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_drawer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdudko <kdudko@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/02 13:59:36 by kdudko            #+#    #+#             */
/*   Updated: 2019/10/02 13:59:38 by kdudko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

static void	draw_menu_julia_set(t_data *data, int i)
{
	int		y;
	int		x;
	t_set	set;

	y = -1;
	while (++y < SP_IMG_H)
	{
		x = -1;
		while (++x < SP_IMG_W)
		{
			set.new_z.re = SP_JX1 + x / (SP_IMG_W - 1.0) * (SP_JX2 - SP_JX1);
			set.new_z.im = SP_JY2 - y / (SP_IMG_H - 1.0) * (SP_JY2 - SP_JY1);
			set.c.re = SP_J1;
			set.c.im = SP_J2;
			count_menu_points(data, &set, i);
			data->small_img[i].iter = set.iter;
			color_menu_point(data, x, y, i);
		}
	}
}

static void	init_menu_fractals(t_data *data, int i)
{
	int		y;
	int		x;
	t_set	set;

	set.f.re = (SP_X2 - SP_X1) / (SP_IMG_W - 1.0);
	set.f.im = (SP_Y2 - SP_Y1) / (SP_IMG_H - 1.0);
	y = -1;
	while (++y < SP_IMG_H && (x = -1))
		while (++x < SP_IMG_W)
		{
			set.c.re = SP_X1 + x * set.f.re;
			set.c.im = SP_Y2 - y * set.f.im;
			if (data->small_img[i].type == tricorn)
				set_complex(&(set.new_z), set.c.re, set.c.im);
			else
				set_complex(&(set.new_z), 0, 0);
			if (data->small_img[i].type == mandelbrot &&
					is_in_mandelbrot_set(set.c.re, set.c.im))
				set.iter = data->params->max_iter;
			else
				count_menu_points(data, &set, i);
			data->small_img[i].iter = set.iter;
			color_menu_point(data, x, y, i);
		}
}

static void	draw_menu_fractals(t_data *data, int i)
{
	if (!(data->small_img[i].m_image = mlx_get_data_addr(
				data->small_img[i].m_img, &(data->small_img[i].bpp),
		&(data->small_img[i].size), &(data->small_img[i].end))))
		error("error");
	if (data->small_img[i].type == julia)
		draw_menu_julia_set(data, i);
	else
		init_menu_fractals(data, i);
}

static void	*draw_app_menu(void *param)
{
	int		j;
	int		i;
	t_data	*data;

	data = (t_data *)param;
	if (!(data->small_img = (t_side_panel *)malloc(sizeof(t_side_panel) *
														SP_IMGS)))
		error(MALLOK_ERROR);
	i = -1;
	j = 0;
	while (++i < total_nb && j < SP_IMGS)
		if (i != data->type)
		{
			data->small_img[j].type = i;
			if (!(data->small_img[j].m_img = mlx_new_image(data->mlx->p_mlx,
								SP_IMG_W, SP_IMG_H)))
				error("error");
			data->small_img[j].mem = i;
			draw_menu_fractals(data, j);
			mlx_put_image_to_window(data->mlx->p_mlx, data->mlx->win,
				data->small_img[j].m_img, IMG_W, j * SP_IMG_H);
			j++;
		}
	pthread_exit(0);
}

void		threads_counting(t_data *data)
{
	pthread_t id;

	if ((pthread_create(&id, NULL, &draw_app_menu, (void *)data)))
		error(PTHREAD_ERROR);
	pthread_join(id, NULL);
}
