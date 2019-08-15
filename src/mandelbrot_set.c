/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot_set.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdudko <kdudko@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 20:18:55 by kdudko            #+#    #+#             */
/*   Updated: 2019/08/14 20:18:58 by kdudko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

void	draw_mandelbrot_set(void)
{
	t_mlx	data;

	if ((data.p_mlx = mlx_init()) == NULL)
		error("Error: mlx init failed in draw_mandelbrot_set()");
	if ((data.p_window = mlx_new_window(data.p_mlx, WIN_WIDTH, WIN_HEIGHT,
										"Mandelbrot Set")) == NULL)
		error("Error: mlx failed to open new window in draw_mandelbrot_set()");
	if (!(data.p_image = mlx_new_image(data.p_mlx, IMG_WIDTH, IMG_HEIGHT)))
		error("Error: mlx failed to create new image in draw_mandelbrot_set()");
	if ((data.img_buffer = mlx_get_data_addr(data.p_image, &(data.bpp),
									&(data.size_line), &(data.endian))) == NULL)
		error("Error: mlx failed to return information about created image\
		in draw_mandelbrot_set()");
	mlx_hook(data.p_window, 2, 0, key_press, &data);
	mlx_hook(data.p_window, 17, 0, close, &data);
	mlx_loop(data.p_mlx);
}
