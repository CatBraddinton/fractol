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

int		expose_hook(t_data *data)
{
	data->mlx->img = mlx_new_image(data->mlx->p_mlx, IMG_W, IMG_H);
	data->mlx->image = mlx_get_data_addr(data->mlx->img,
		&(data->mlx->bpp), &(data->mlx->size), &(data->mlx->end));
	draw_fractals(data);
	mlx_put_image_to_window(data->mlx->p_mlx, data->mlx->win,
		data->mlx->img, 0, 0);
	return (0);
}

void	draw_choosen_fractal(t_data *data, int y)
{
	int	i;

	if (y == 1200)
		i = 2;
	else
		i = y / SIDE_PANEL_IMG_H;
		data->type = data->small_img[i].mem;
		mlx_destroy_image(data->mlx->p_mlx, data->mlx->img);
		i = -1;
		while (++i < SIDE_PANEL_IMGS)
			mlx_destroy_image(data->mlx->p_mlx, data->small_img[i].m_img);
		mlx_clear_window(data->mlx->p_mlx, data->mlx->win);
		init_params(data);
		init_extremums(data);

		create_image(data);
}

int		mouse_hook(int button, int x, int y, t_data *data)
{
	if (data->mouse_left_key == 1)
		return (-1);
	if (data->mouse_left_key == 0 && button == KEY_MOUSE_LEFT
		&& x > IMG_W && x <= data->mlx->win_w)
	{
		data->mouse_left_key = 1;
		draw_choosen_fractal(data, y);
	}

	else if (data->params->zoom == 1.1 && button == KEY_MOUSE_SCROLL_DOWN)
		return (1);
	else if (x < IMG_W && y < IMG_H)
	{
		if (button == KEY_MOUSE_SCROLL_UP)
		{
			data->params->move.re = data->min.re +
			x * (data->max.re - data->min.re) / (IMG_W - 1.0);
			data->params->move.im = data->max.im -
			y * (data->max.im - data->min.im) / (IMG_H - 1.0);
			data->params->zoom += 0.0001;
			data->params->zoom_factor = data->params->zoom;
		}
		if (button == KEY_MOUSE_SCROLL_DOWN)
		{
			data->params->zoom -= 0.0001;
			data->params->zoom_factor = 1.0 / data->params->zoom;
		}
		zoom(data, data->params->move.re,
				data->params->move.im, data->params->zoom_factor);
		mlx_destroy_image(data->mlx->p_mlx, data->mlx->img);
		expose_hook(data);
	}
	return (1);
}

void	move_image(t_data *data, int keycode)
{
	if (keycode == KEY_UP)
	{
		set_complex(&(data->min), data->min.re, data->min.im + 0.01);
		set_complex(&(data->max), data->max.re, data->max.im + 0.01);
	}
	if (keycode == KEY_DOWN)
	{
		set_complex(&(data->min), data->min.re, data->min.im - 0.01);
		set_complex(&(data->max), data->max.re, data->max.im - 0.01);
	}
	if (keycode == KEY_LEFT)
	{
		set_complex(&(data->min), data->min.re - 0.01, data->min.im);
		set_complex(&(data->max), data->max.re - 0.01, data->max.im);
	}
	if (keycode == KEY_RIGHT)
	{
		set_complex(&(data->min), data->min.re + 0.01, data->min.im);
		set_complex(&(data->max), data->max.re + 0.01, data->max.im);
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
		if (keycode == KEY_K)
			if (data->params->max_iter > 10)
				data->params->max_iter -= 10;
		if (keycode == KEY_M)
			data->julia_mouse_lock = (data->julia_mouse_lock == 0) ? 1 : 0;
		if (keycode == KEY_NUM_CLEAR && data->params->zoom != 1.1)
		{
			init_extremums(data);
			data->params->zoom = 1.1;
			data->params->zoom_factor = 0;
		}
		if (keycode == KEY_UP || keycode == KEY_DOWN
			|| keycode == KEY_LEFT || keycode == KEY_RIGHT)
			move_image(data, keycode);
		mlx_destroy_image(data->mlx->p_mlx, data->mlx->img);
		expose_hook(data);
	}
	return (1);
}
