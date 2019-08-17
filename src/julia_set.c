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

#include "../inc/fractol.h"

void	draw_julia_set(t_data *data)
{
	if ((data->mlx_data->p_mlx = mlx_init()) == NULL)
		error("Error: mlx init failed in draw_mandelbrot_set()");
	if (!(data->mlx_data->p_window = mlx_new_window(data->mlx_data->p_mlx,
		data->win_width, data->win_height, "Julia Set")))
		error("Error: mlx failed to open new window in draw_mandelbrot_set()");
	if (!(data->mlx_data->p_image = mlx_new_image(data->mlx_data->p_mlx,
		data->img_width, data->img_height)))
		error("Error: mlx failed to create new image in draw_mandelbrot_set()");
	if ((data->mlx_data->img_buffer = mlx_get_data_addr(data->mlx_data->p_image,
		&(data->mlx_data->bpp), &(data->mlx_data->size_line),
		&(data->mlx_data->endian))) == NULL)
		error("Error: mlx failed to return information about created image\
		in draw_mandelbrot_set()");
	mlx_hook(data->mlx_data->p_window, 2, 0, key_press, &data);
	mlx_hook(data->mlx_data->p_window, 17, 0, close, &data);
	mlx_loop(data->mlx_data->p_mlx);
}
