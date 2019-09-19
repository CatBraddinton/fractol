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
