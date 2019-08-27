/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia_set.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdudko <kdudko@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 23:40:56 by kdudko            #+#    #+#             */
/*   Updated: 2019/08/14 23:40:58 by kdudko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/mandelbrot_and_julia.h"

void	draw_julia_set(t_data *data)
{
	if ((data->img_buffer = mlx_get_data_addr(data->p_image, &(data->bpp),
	&(data->size_line), &(data->endian))) == NULL)
		error("Error: mlx failed to return information about created image\
		in draw_julia_set()");
	data->max_iter = 1500;
}
