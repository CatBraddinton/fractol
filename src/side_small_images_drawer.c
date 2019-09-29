/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   side_small_images_drawer.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdudko <kdudko@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 12:31:05 by kdudko            #+#    #+#             */
/*   Updated: 2019/09/28 12:31:07 by kdudko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

void	draw_menu_fractals(t_data *data, int i)
{
	if (!(data->small_img[i].m_image = mlx_get_data_addr(
				data->small_img[i].m_img, &(data->small_img[i].bpp),
		&(data->small_img[i].size), &(data->small_img[i].end))))
		error("error");
	if (data->small_img[i].type == julia)
	{
		set_complex(&(data->small_img[i].m_min), -2.5, -2.0);
		set_complex(&(data->small_img[i].m_max), 2.5, 2.0);
		set_complex(&(data->small_img[i].j_k), 0.1234, 0.653);
		draw_menu_julia_set(data, i);
	}
	else
	{
		set_complex(&(data->small_img[i].m_min), -3.5, -2.5);
		set_complex(&(data->small_img[i].m_max), 3.5, 2.5);
		if (data->small_img[i].type == mandelbrot)
			draw_menu_mandelbrot_set(data, i);
		if (data->small_img[i].type == tricorn)
			draw_menu_tricorn_fractal(data, i);
		if (data->small_img[i].type == burning_ship)
			draw_menu_burning_ship_fractal(data, i);
	}
}

void	*draw_app_menu(void *param)
{
	int		j;
	int		i;
	t_data	*data;

	data = (t_data *)param;
	if (!(data->small_img = (t_side_panel *)malloc(SIDE_PANEL_IMGS *
	sizeof(t_side_panel))))
		error(MALLOK_ERROR);
	i = -1;
	j = 0;
	while (++i < total_nb && j < SIDE_PANEL_IMGS)
		if (i != data->type)
		{
			data->small_img[j].max_iter = 100;
			data->small_img[j].type = i;
			if (!(data->small_img[j].m_img = mlx_new_image(data->mlx->p_mlx,
								SIDE_PANEL_IMG_W, SIDE_PANEL_IMG_H)))
				error("error");
			data->small_img[j].mem = i;
			draw_menu_fractals(data, j);
			mlx_put_image_to_window(data->mlx->p_mlx, data->mlx->win,
			data->small_img[j].m_img, IMG_W, j * SIDE_PANEL_IMG_H);
			j++;
		}
	pthread_exit(0);
}
