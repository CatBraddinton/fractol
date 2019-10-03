/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdudko <kdudko@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 23:57:08 by kdudko            #+#    #+#             */
/*   Updated: 2019/08/14 23:57:09 by kdudko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

void	draw_choosen_fractal(t_data *data, int y)
{
	t_type	i;

	if (y == 1200)
		i = 2;
	else
		i = y / SP_IMG_H;
	data->type = data->img[i].mem;
	mlx_destroy_image(data->mlx->p_mlx, data->mlx->img);
	i = -1;
	while (++i < SP_IMGS)
		mlx_destroy_image(data->mlx->p_mlx, data->img[i].m_img);
	free(data->img);
	mlx_clear_window(data->mlx->p_mlx, data->mlx->win);
	init_extremums(data);
	init_params(data);
	threads_counting(data);
	expose_hook(data);
	data->mouse_left_key = 0;
}

int		mouse_hook(int button, int x, int y, t_data *data)
{
	if (data->show_side_panel == 1 && button == KEY_MOUSE_LEFT &&
		x > IMG_W && x <= data->mlx->win_w && y >= 0 && y < data->mlx->im_w &&
		data->mouse_left_key == 0)
	{
		data->mouse_left_key = 1;
		draw_choosen_fractal(data, y);
	}
	else if ((button == KEY_MOUSE_SCROLL_UP) ||
		(button == KEY_MOUSE_SCROLL_DOWN))
	{
		if (data->params->zoom == 1.1 && button == KEY_MOUSE_SCROLL_DOWN)
			return (1);
		if (x < data->mlx->im_w && y < IMG_H)
			zoom_image(button, x, y, data);
	}
	return (1);
}

void	show_hide_menu(t_data *data, int keycode)
{
	if (keycode == KEY_HOME && data->show_side_panel == 0)
	{
		data->show_side_panel = 1;
		data->mlx->im_w = IMG_W;
		threads_counting(data);
	}
	if (keycode == KEY_END && data->show_side_panel == 1)
	{
		data->show_side_panel = 0;
		mlx_destroy_image(data->mlx->p_mlx, data->img[0].m_img);
		mlx_destroy_image(data->mlx->p_mlx, data->img[1].m_img);
		mlx_destroy_image(data->mlx->p_mlx, data->img[2].m_img);
		free(data->img);
		mlx_clear_window(data->mlx->p_mlx, data->mlx->win);
		data->mlx->im_w = data->mlx->win_w - 20;
	}
}

int		key_press(int keycode, t_data *data)
{
	if (keycode == KEY_ESC)
		exit(EXIT_SUCCESS);
	if (data->mlx->img)
	{
		if (keycode == KEY_I)
			data->params->max_iter += 10;
		if (keycode == KEY_K && data->params->max_iter > 10)
			data->params->max_iter -= 10;
		if (keycode == KEY_M)
			data->julia_mouse_lock = (data->julia_mouse_lock == 0) ? 1 : 0;
		if (keycode == KEY_NUM_CLEAR && data->params->zoom != 1.1)
		{
			init_extremums(data);
			data->params->zoom = 1.1;
			data->params->zoom_f = 0;
		}
		if (keycode == KEY_HOME || keycode == KEY_END)
			show_hide_menu(data, keycode);
		mlx_destroy_image(data->mlx->p_mlx, data->mlx->img);
		expose_hook(data);
	}
	return (1);
}
