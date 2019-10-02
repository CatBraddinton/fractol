/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia_set.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdudko <kdudko@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 23:19:20 by kdudko            #+#    #+#             */
/*   Updated: 2019/09/27 23:19:22 by kdudko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

void	draw_julia_set(t_data *data, int x, int y, int i)
{
	t_set set;

	set.new_z.re = data->min.re + x /
		(IMG_W - 1.0) * (data->max.re - data->min.re);
	set.new_z.im = data->max.im - y /
		(IMG_H - 1.0) * (data->max.im - data->min.im);
	set.c.re = data->params->julia_k.re;
	set.c.im = data->params->julia_k.im;
	count_points(data, &set);
	data->iter[i] = set.iter;
	color_point(data, x, y, i);
}

int		julia_motion(int x, int y, t_data *data)
{
	if (data->type == julia && data->julia_mouse_lock == 0 &&
		x <= IMG_W && y <= IMG_H)
	{
		data->params->mouse.re = 4 * ((double)x / IMG_W - 0.5);
		data->params->mouse.im = 4 * ((double)y / IMG_H - 0.5);
		set_complex(&(data->params->julia_k),
					data->params->mouse.re, data->params->mouse.im);
		mlx_destroy_image(data->mlx->p_mlx, data->mlx->img);
		expose_hook(data);
	}
	return (1);
}

void	draw_menu_julia_set(t_data *data, int i)
{
	int		y;
	int		x;
	t_set	set;

	y = -1;
	while (++y < SIDE_PANEL_IMG_H)
	{
		x = -1;
		while (++x < SIDE_PANEL_IMG_W)
		{
			set.new_z.re = data->small_img[i].m_min.re + x /
			(SIDE_PANEL_IMG_W - 1.0) * (data->small_img[i].m_max.re -
											data->small_img[i].m_min.re);
			set.new_z.im = data->small_img[i].m_max.im - y /
			(SIDE_PANEL_IMG_H - 1.0) * (data->small_img[i].m_max.im -
										data->small_img[i].m_min.im);
			set.c.re = data->small_img[i].j_k.re;
			set.c.im = data->small_img[i].j_k.im;
			count_menu_points(data, &set, i);
			data->small_img[i].iter = set.iter;
			color_menu_point(data, x, y, i);
		}
	}
}
