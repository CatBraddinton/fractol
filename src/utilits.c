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
	if (!(data->buff = (int **)malloc(data->image_height * sizeof(int *))))
		error("malloc error");
	while (++i < data->image_height)
		if (!(data->buff[i] = (int *)malloc(data->image_width * sizeof(int))))
			error("malloc error");
}

void	init_params(t_data *data)
{
	data->menu_width = WIN_WIDTH / 5;
	data->menu_height = WIN_HEIGHT;
	data->image_width = WIN_WIDTH - data->menu_width;
	data->image_height = WIN_HEIGHT;
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
	data->params->center_x = fabs(data->re_max) + fabs(data->re_min) / 2.0;
	data->params->center_y = fabs(data->im_max) + fabs(data->im_min) / 2.0;
	data->params->move_x = 0.0;
	data->params->move_y = 0.0;
	data->params->scale_x = (data->re_max - data->re_min) / data->image_width;
	data->params->scale_y = (data->im_max - data->im_min) / data->image_height;
	data->im_offset_x = 0;
	data->im_offset_y = 0;
}
