/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdudko <kdudko@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 17:45:40 by kdudko            #+#    #+#             */
/*   Updated: 2019/09/17 17:45:42 by kdudko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

void	draw_fractals(t_data *data)
{
	void (*draw_fractal[total_nb]) (t_data *data);

	draw_fractal[mandelbrot] = draw_mandelbrot_set;
	draw_fractal[julia] = draw_julia_set;
	(*draw_fractal[data->type])(data);
}

void	draw_fractal_image(char *name)
{
	t_data 		*data;

	if ((data = (t_data *)malloc(sizeof(t_data))) == NULL)
		error(strerror(errno));
	get_fractal_type(&(data->type), name);
	init_programm_architecture(data);
	set_complex(&(data->min), -2.0, -1.0);
	set_complex(&(data->max), 1.0, 1.0);
	if ((data->mlx->p_mlx = mlx_init()) == NULL)
		error(strerror(errno));
	if (!(data->mlx->win = mlx_new_window(data->mlx->p_mlx, WIN_W, WIN_H, name)))
		error(strerror(errno));
	data->mlx->img = mlx_new_image(data->mlx->p_mlx, data->mlx->image_width,
											data->mlx->image_height);
	data->mlx->image = mlx_get_data_addr(data->mlx->img,
			&(data->mlx->bpp), &(data->mlx->size), &(data->mlx->end));
	draw_fractals(data);
	mlx_hook(data->mlx->win, 2, 0, key_press, data);
	mlx_hook(data->mlx->win, 4, 0, mouse_press, data);
	mlx_hook(data->mlx->win, 6, 0, mouse_move, data);
	mlx_hook(data->mlx->win, 17, 0, close, data);
	mlx_loop(data->mlx->p_mlx);
}
