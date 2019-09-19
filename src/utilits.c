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
	data->params->iter = 0;
	set_complex(&(data->set->k), data->params->mouse_x, data->params->mouse_y);
	data->params->center_x = (data->min.re + data->max.re) / 2.0;
	data->params->center_y = (data->min.im + data->max.im) / 2.0;
	data->params->move_x = 0.0;
	data->params->move_y = 0.0;
}
