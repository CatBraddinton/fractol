/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilits.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdudko <kdudko@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 20:45:18 by kdudko            #+#    #+#             */
/*   Updated: 2019/08/14 20:45:20 by kdudko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

void	free_buff(int **buff, int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		free(buff[i]);
		i++;
	}
	free(buff);
}

void	set_complex(t_cnum *n, double real, double imaginary)
{
	n->re = real;
	n->im = imaginary;
}

void	init_buffer(t_data *data)
{
	int i;

	i = -1;
	if (!(data->buff = (int **)malloc(data->mlx->image_height * sizeof(int *))))
		error("malloc error");
	while (++i < data->mlx->image_height)
		if (!(data->buff[i] = (int *)malloc(data->mlx->image_width * sizeof(int))))
			error("malloc error");
}

void	init_params(t_data *data)
{
	data->menu->menu_width = WIN_W / 5;
	data->menu->menu_height = WIN_H;
	data->mlx->image_width = WIN_W - data->menu->menu_width;
	data->mlx->image_height = WIN_H;
	data->params->max_iter = MAX_ITER;
	data->params->iter = 0;
	data->re_min = -2.0;
	data->im_min = -1.0;
	data->im_max = 1.0;
	data->re_max = 1.0;
	data->mlx->bpp = 0;
	data->mlx->size = 0;
	data->mlx->end = 0;
	data->params->zoom = 1.1;
	data->params->mouse_x = 0;
	data->params->mouse_y = 0;
	data->params->center_x = (data->re_min + data->re_max) / 2.0;
	data->params->center_y = (data->im_min + data->im_max) / 2.0;
	data->params->move_x = 0.0;
	data->params->move_y = 0.0;
}
