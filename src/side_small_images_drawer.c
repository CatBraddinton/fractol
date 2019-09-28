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
		set_complex(&(data->small_img[i].m_min), -3.0, -3.0);
		set_complex(&(data->small_img[i].m_max), 3.0, 3.0);
		set_complex(&(data->small_img[i].j_k), 0.3, 0.6);
		draw_menu_julia_set(data, i);
	}
	else
	{
		set_complex(&(data->small_img[i].m_min), -2.5, -1.0);
		set_complex(&(data->small_img[i].m_max), 1.0, 1.0);
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
	if (!(data->small_img = (t_side_panel *)malloc(3 * sizeof(t_side_panel))))
		error(MALLOK_ERROR);
	i = -1;
	j = 0;
	while (++i < total_nb)
		if (i != data->type)
		{
			data->small_img[j].type = i;
			data->small_img[j].w = 600;
			data->small_img[j].h = 400;
			if (!(data->small_img[j].m_img = mlx_new_image(data->mlx->p_mlx,
								data->small_img[j].w, data->small_img[j].h)))
				error("error");
			draw_menu_fractals(data, j);
			mlx_put_image_to_window(data->mlx->p_mlx, data->mlx->win,
			data->small_img[j].m_img, IMG_W, j * data->small_img[j].h);
			j++;
		}
	pthread_exit(0);
}
