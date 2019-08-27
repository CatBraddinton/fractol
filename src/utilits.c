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
#include "../inc/mandelbrot_and_julia.h"

void	count_fractal(t_data *data)
{
	void (*draw_fractal[TOTAL_NB]) (t_data *data);

	draw_fractal[0] = draw_julia_set;
	draw_fractal[1] = draw_mandelbrot_set;
	draw_fractal[2] = NULL;
	(*draw_fractal[data->type - 1])(data);
}

void	init_params(t_data *data)
{
	data->bpp = 0;
	data->size_line = 0;
	data->endian = 0;
	data->zoom = 0.5;
	data->pos_left = 0;
	data->pos_right = 0;
	data->pos_up = 0;
	data->pos_down = 0;
}

void	mlx(t_data *data)
{
	init_params(data);
	if ((data->p_mlx = mlx_init()) == NULL)
		error("Error: mlx init failed in mlx()");
	if (!(data->p_window = mlx_new_window(data->p_mlx, WIDTH, HEIGHT,
		data->name)))
		error("Error: mlx failed to open new window in mlx()");
	if (!(data->p_image = mlx_new_image(data->p_mlx, WIDTH, HEIGHT)))
		error("Error: mlx failed to create new image in mlx()");
	count_fractal(data);
	mlx_put_image_to_window(data->p_mlx, data->p_window, data->p_image,	0, 0);
	mlx_hook(data->p_window, 2, 0, key_press, &data);
	mlx_hook(data->p_window, 17, 0, close, &data);
	mlx_loop(data->p_mlx);
}
