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
#include "../inc/mandelbrot_set.h"
void	init_cam(t_data *data)
{
	data->cam.center_x = IMG_WIDTH / 2;
	data->cam.center_y = IMG_HEIGHT / 2;
	data->cam.origin_x = WIN_WIDTH / 2;
	data->cam.origin_y = WIN_HEIGHT / 2;
	data->cam.offset_x = data->cam.origin_x - data->cam.center_x;
	data->cam.offset_y = data->cam.origin_y - data->cam.center_y;
}

void	count_fractal(t_data *data)
{
	void (*draw_fractal[TOTAL_NB]) (t_data *data);

	draw_fractal[0] = NULL;
	draw_fractal[1] = draw_mandelbrot_set;
	draw_fractal[2] = NULL;
	(*draw_fractal[data->type - 1])(data);
}

void	mlx(t_data *data)
{
	data->bpp = 0;
	data->size_line = 0;
	data->endian = 0;
	data->cam.zoom = 1.0;
	if ((data->p_mlx = mlx_init()) == NULL)
		error("Error: mlx init failed in draw_mandelbrot_set()");
	if (!(data->p_window = mlx_new_window(data->p_mlx, WIN_WIDTH, WIN_HEIGHT,
		"fractol")))
		error("Error: mlx failed to open new window in draw_mandelbrot_set()");
	count_fractal(data);
	mlx_hook(data->p_window, 2, 0, key_press, &data);
	mlx_hook(data->p_window, 17, 0, close, &data);
	mlx_loop(data->p_mlx);
}
