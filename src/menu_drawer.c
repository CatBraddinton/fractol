/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_drawer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdudko <kdudko@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 09:38:46 by kdudko            #+#    #+#             */
/*   Updated: 2019/09/28 09:40:07 by kdudko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

void	draw_menu_fractals(t_data *data, int i)
{
	if (!(data->menu->slot[i].m_image = mlx_get_data_addr(
				data->menu->slot[i].m_img, &(data->menu->slot[i].bpp),
		&(data->menu->slot[i].size), &(data->menu->slot[i].end))))
		error("error");
	if (data->menu->slot[i].type == julia)
	{
		set_complex(&(data->menu->slot[i].m_min), -3.0, -3.0);
		set_complex(&(data->menu->slot[i].m_max), 3.0, 3.0);
		set_complex(&(data->menu->slot[i].j_k), 0.3, 0.6);
		draw_menu_julia_set(data, i);
	}
	else
	{
		set_complex(&(data->menu->slot[i].m_min), -2.5, -1.0);
		set_complex(&(data->menu->slot[i].m_max), 1.0, 1.0);
		if (data->menu->slot[i].type == mandelbrot)
			draw_menu_mandelbrot_set(data, i);
		if (data->menu->slot[i].type == tricorn)
			draw_menu_tricorn_fractal(data, i);
		if (data->menu->slot[i].type == burning_ship)
			draw_menu_burning_ship_fractal(data, i);
	}
}

void	*draw_app_menu(void *param)
{
	int		j;
	int		i;
	t_data	*data;

	data = (t_data *)param;
	if (!(data->menu->slot = (t_mimg *)malloc(3 * sizeof(t_mimg))))
		error("malloc error");
	i = -1;
	j = 0;
	while (++i < total_nb)
		if (i != data->type)
		{
			data->menu->slot[j].type = i;
			data->menu->slot[j].w = 600;
			data->menu->slot[j].h = 400;
			if (!(data->menu->slot[j].m_img = mlx_new_image(data->mlx->p_mlx,
								data->menu->slot[j].w, data->menu->slot[j].h)))
				error("error");
			draw_menu_fractals(data, j);
			mlx_put_image_to_window(data->mlx->p_mlx, data->mlx->win,
			data->menu->slot[j].m_img, IMG_W, j * data->menu->slot[j].h);
			j++;
		}
	pthread_exit(0);
}
