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

void	draw_fractals(t_data *data)
{
	void (*draw_fractal[TOTAL_NB]) (t_data *data);

	draw_fractal[0] = draw_mandelbrot_julia;
	draw_fractal[1] = draw_mandelbrot_julia;
	draw_fractal[2] = NULL;
	(*draw_fractal[data->type - 1])(data);
}

void	init_params(t_data *data)
{
	data->bpp = 0;
	data->size_line = 0;
	data->endian = 0;
	data->max_iter = MAX_ITER;
	data->mouse_x = 0;
	data->mouse_y = 0;
	data->cam->zoom = 0.7;
	data->cam->origin_x = WIDTH / 2;
	data->cam->origin_y = HEIGHT / 2;
}

void	mlx(t_data *data)
{
	if ((data->p_mlx = mlx_init()) == NULL)
		error("Error: mlx init failed in mlx()");
	if (!(data->p_window = mlx_new_window(data->p_mlx, WIDTH, HEIGHT,
		data->name)))
		error("Error: mlx failed to open new window in mlx()");
	draw_fractals(data);
	mlx_hook(data->p_window, 2, 0, key_press, data);
	mlx_hook(data->p_window, 4, 0, mouse_press, data);
	mlx_hook(data->p_window, 6, 0, mouse_move, data);
	mlx_hook(data->p_window, 17, 0, close, data);
	mlx_loop(data->p_mlx);
}
