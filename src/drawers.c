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

void		draw_menu_frame(t_data *data)
{
	int x;
	int y;

	y = -1;
	while (++y < MENU_H && (x = (IMG_W + 10)))
		while (++x < (IMG_W + 20))
			mlx_pixel_put(data->mlx->p_mlx, data->mlx->win, x, y, 0x80D0C7);
	y = 410;
	while (++y < 420 && (x = (IMG_W + 19)))
		while (++x < data->mlx->win_w)
			mlx_pixel_put(data->mlx->p_mlx, data->mlx->win, x, y, 0x80D0C7);
	y = 820;
	while (++y < 830 && (x = (IMG_W + 19)))
		while (++x < data->mlx->win_w)
			mlx_pixel_put(data->mlx->p_mlx, data->mlx->win, x, y, 0x80D0C7);
}

void		draw_frame(t_data *data)
{
	int x;
	int y;

	y = -1;
	while (++y < MENU_H && (x = -1))
		while (++x < 10)
			mlx_pixel_put(data->mlx->p_mlx, data->mlx->win, x, y, 0x80D0C7);
	y = -1;
	while (++y < 10 && (x = -1))
		while (++x < data->mlx->win_w)
			mlx_pixel_put(data->mlx->p_mlx, data->mlx->win, x, y, 0x80D0C7);
	y = MENU_H - 10;
	while (++y < MENU_H && (x = -1))
		while (++x < data->mlx->win_w)
			mlx_pixel_put(data->mlx->p_mlx, data->mlx->win, x, y, 0x80D0C7);
	y = -1;
	while (++y < MENU_H && (x = data->mlx->win_w - 10))
		while (++x < data->mlx->win_w)
			mlx_pixel_put(data->mlx->p_mlx, data->mlx->win, x, y, 0x80D0C7);
	if (data->show_side_panel == 1)
		draw_menu_frame(data);
}

int			expose_hook(t_data *data)
{
	draw_frame(data);
	data->mlx->img = mlx_new_image(data->mlx->p_mlx, data->mlx->im_w, IMG_H);
	data->mlx->image = mlx_get_data_addr(data->mlx->img,
		&(data->mlx->bpp), &(data->mlx->size), &(data->mlx->end));
	draw_fractals(data);
	mlx_put_image_to_window(data->mlx->p_mlx, data->mlx->win,
		data->mlx->img, 10, 10);
	return (0);
}

static int	get_fractal_type(char *input)
{
	int len;

	len = (int)ft_strlen(input);
	if (len == 5 && ft_strnequ(input, "julia", len))
		return (julia);
	if (len == 10 && ft_strnequ(input, "mandelbrot", len))
		return (mandelbrot);
	if (len == 7 && ft_strnequ(input, "tricorn", len))
		return (tricorn);
	if (len == 12 && ft_strnequ(input, "burning_ship", len))
		return (burning_ship);
	return (-1);
}

void		draw_fractal_image(char *name)
{
	t_data *data;

	if ((data = (t_data *)malloc(sizeof(t_data))) == NULL)
		error(MALLOK_ERROR);
	data->type = get_fractal_type(name);
	if (data->type == invalid)
		error(TYPE_ERROR);
	init_programm_architecture(data);
	if ((data->mlx->p_mlx = mlx_init()) == NULL)
		error(MLX_ERROR);
	data->mlx->win = mlx_new_window(data->mlx->p_mlx, data->mlx->win_w,
													data->mlx->win_h, name);
	if (!(data->mlx->win))
		error(MLX_ERROR);
	threads_counting(data);
	mlx_expose_hook(data->mlx->win, expose_hook, data);
	mlx_hook(data->mlx->win, 2, 0, key_press, data);
	mlx_hook(data->mlx->win, 6, 0, julia_motion, data);
	mlx_hook(data->mlx->win, 17, 0, close, data);
	mlx_mouse_hook(data->mlx->win, mouse_hook, data);
	mlx_do_key_autorepeaton(data->mlx->p_mlx);
	mlx_loop(data->mlx->p_mlx);
}
