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
	void (*draw_fractal[TOTAL_NB]) (t_data *data);

	draw_fractal[0] = draw_julia_set;
	draw_fractal[1] = draw_mandelbrot_set;
	(*draw_fractal[data->type - 1])(data);
}

void	init_programe_architecture(t_data *data)
{
	if ((data->menu = (t_menu *)malloc(sizeof(t_menu))) == NULL)
		error(strerror(errno));
	data->menu->menu_width = WIN_W / 5;
	data->menu-> menu_height = WIN_H;
	data->menu-> start_x = WIN_W - data->menu->menu_width;
	data->menu-> start_y = 0 ;
	data->menu-> finish_x = WIN_W;
	data->menu-> finish_y = WIN_H;
	if ((data->mlx = (t_mlx *)malloc(sizeof(t_mlx))) == NULL)
		error(strerror(errno));
	data->mlx->image_width = WIN_W - data->menu->menu_width;
	data->mlx->image_height = WIN_H;
	data->mlx->bpp = 0;
	data->mlx->size = 0;
	data->mlx->end = 0;
	if ((data->params = (t_params *)malloc(sizeof(t_params))) == NULL)
		error(strerror(errno));
	if ((data->set = (t_set *)malloc(sizeof(t_set))) == NULL)
		error(strerror(errno));
	data->params->max_iter = MAX_ITER;
	set_complex(&(data->min), -2.0, -1.0);
	set_complex(&(data->max), 1.0, 1.0);
	set_complex(&(data->set->mouse), -0.4, 0.6);
	data->params->zoom = 1.1;
}

void	draw_fractal_image(char *name)
{
	t_data 		*data;

	if ((data = (t_data *)malloc(sizeof(t_data))) == NULL)
		error(strerror(errno));
	if ((data->type = get_fractal_type(name)) == 0)
		invalid_param();
	init_programe_architecture(data);
	if ((data->mlx->p_mlx = mlx_init()) == NULL)
		error(strerror(errno));
	if (!(data->mlx->win = mlx_new_window(data->mlx->p_mlx, WIN_W, WIN_H, name)))
		error(strerror(errno));
	init_params(data);
	draw_fractals(data);
	mlx_hook(data->mlx->win, 2, 0, key_press, data);
	mlx_hook(data->mlx->win, 4, 0, mouse_press, data);
	mlx_hook(data->mlx->win, 6, 0, mouse_move, data);
	mlx_hook(data->mlx->win, 17, 0, close, data);
	mlx_loop(data->mlx->p_mlx);
}
