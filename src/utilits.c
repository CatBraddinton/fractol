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

void	init_params(t_data *data)
{
	data->params->max_iter = MAX_ITER;
	data->params->zoom = 1.1;
	data->params->zoom_f = 0;
	set_complex(&(data->params->julia_k), 0.3, 0.6);
	data->julia_mouse_lock = 1;
	data->color_style = 1;
	data->show_side_panel = 1;
}

void	init_programm_architecture(t_data *data)
{
	if ((data->mlx = (t_mlx *)malloc(sizeof(t_mlx))) == NULL)
		error(MALLOK_ERROR);
	data->mlx->win = 0;
	data->mlx->win_w = IMG_W + MENU_W + 30;
	data->mlx->win_h = (IMG_H > MENU_H) ? IMG_H : MENU_H;
	data->mlx->im_w = IMG_W;
	data->mlx->img = NULL;
	data->mlx->bpp = 0;
	data->mlx->size = 0;
	data->mlx->end = 0;
	if ((data->params = (t_params *)malloc(sizeof(t_params))) == NULL)
		error(MALLOK_ERROR);
	init_params(data);
	init_extremums(data);
}

void	init_extremums(t_data *data)
{
	if (data->type == julia)
	{
		set_complex(&(data->min), -3.0, -3.0);
		set_complex(&(data->max), 3.0, 3.0);
	}
	else
	{
		set_complex(&(data->min), -4.5, -3.0);
		set_complex(&(data->max), 4.5, 3.0);
	}
}

void	set_complex(t_cnum *n, double real, double imaginary)
{
	n->re = real;
	n->im = imaginary;
}
