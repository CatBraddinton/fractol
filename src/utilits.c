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
	{
		if (!(data->buff[i] = (int *)malloc(data->mlx->image_width * sizeof(int))))
			error("malloc error");
		ft_memset(data->buff[i], 0, data->mlx->image_width);
	}
}

void	init_params(t_data *data)
{
	zoom(data, data->set->move.re, data->set->move.im, data->params->zoom_factor);
	// set_complex(&(data->set->center), ((data->min.re + data->max.re) / 2.0),
	// 				((data->min.im + data->max.im) / 2.0));
	// set_complex(&(data->set->offset), data->set->move.re -
	// 	data->set->center.re, data->set->move.im - data->set->center.im);
	// set_complex(&(data->min), data->min.re + data->set->offset.re,
	// 		data->min.im + data->set->offset.im);
	// set_complex(&(data->max), data->max.re + data->set->offset.re,
	// 	data->max.im + data->set->offset.im);
}
