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

void	set_complex(t_cnum *n, double real, double imaginary)
{
	n->re = real;
	n->im = imaginary;
}

void	init_mlx_window(t_data *data, char *name)
{
	if ((data->mlx->p_mlx = mlx_init()) == NULL)
		error(strerror(errno));
	data->mlx->win = mlx_new_window(data->mlx->p_mlx, WIN_W, WIN_H, name);
	if (!(data->mlx->win))
		error(strerror(errno));
	mlx_expose_hook(data->mlx->win, expose_hook, data);
	mlx_hook(data->mlx->win, 2, 0, key_press, data);
	mlx_hook(data->mlx->win, 6, 0, julia_motion, data);
	mlx_hook(data->mlx->win, 17, 0, close, data);
	mlx_mouse_hook(data->mlx->win, mouse_hook, data);
	mlx_do_key_autorepeaton(data->mlx->p_mlx);
	mlx_loop(data->mlx->p_mlx);
}

void	init_programm_architecture(t_data *data)
{
	if ((data->menu = (t_menu *)malloc(sizeof(t_menu))) == NULL)
		error(strerror(errno));
	data->menu->menu_width = WIN_W / 5;
	data->menu-> menu_height = WIN_H;
	data->menu-> start_x = WIN_W - data->menu->menu_width;
	data->menu-> start_y = 0;
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
	data->params->max_iter = MAX_ITER;
	data->params->zoom = 1.1;
	data->params->zoom_factor = 0;
	set_complex(&(data->params->julia_k), 0.4, -0.6);
}
