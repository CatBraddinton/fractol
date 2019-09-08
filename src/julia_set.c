/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia_set.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdudko <kdudko@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 12:06:10 by kdudko            #+#    #+#             */
/*   Updated: 2019/09/07 12:06:13 by kdudko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/julia.h"

void	draw_julia_set(t_data *data)
{
	int 	y;
	int 	x;

	init_buffer(data);
	y = -1;
	while (++y < HEIGHT && (x = -1))
		while (++x < WIDTH)
		{
			convert_pixels(&(data->set.new_z), data, x, y);
			data->params->iter = 0;
			while (data->params->iter < data->params->max_iter)
			{
				init_complex(&(data->set.old_z), data->set.new_z.re, data->set.new_z.im);
				data->set.new_z.re = data->set.old_z.re * data->set.old_z.re -
					data->set.old_z.im * data->set.old_z.im + data->set.k.re;
				data->set.new_z.im = 2.0 * data->set.old_z.re * data->set.old_z.im + data->set.k.im;
				data->params->iter++;
				if ((pow(data->set.new_z.re , 2.0) + pow(data->set.new_z.im, 2.0))
					> 4)
					break ;
			}
			data->buff[y][x] = data->params->iter;
		}
	color_point(data,data->buff);
	free_buff(data->buff);
}
