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

int			expose_hook(t_data *data)
{
	data->mlx->img = mlx_new_image(data->mlx->p_mlx, IMG_W, IMG_H);
	data->mlx->image = mlx_get_data_addr(data->mlx->img,
		&(data->mlx->bpp), &(data->mlx->size), &(data->mlx->end));
	draw_fractals(data);
	mlx_put_image_to_window(data->mlx->p_mlx, data->mlx->win,
		data->mlx->img, 0, 0);
	return (0);
}

static void	create_image(t_data *data)
{
	threads_counting(data);
	mlx_expose_hook(data->mlx->win, expose_hook, data);
	mlx_hook(data->mlx->win, 2, 0, key_press, data);
	mlx_hook(data->mlx->win, 6, 0, julia_motion, data);
	mlx_hook(data->mlx->win, 17, 0, close, data);
	mlx_mouse_hook(data->mlx->win, mouse_hook, data);
	mlx_do_key_autorepeaton(data->mlx->p_mlx);
	mlx_loop(data->mlx->p_mlx);
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
	init_extremums(data);
	if ((data->mlx->p_mlx = mlx_init()) == NULL)
		error(MLX_ERROR);
	data->mlx->win = mlx_new_window(data->mlx->p_mlx, data->mlx->win_w,
													data->mlx->win_h, name);
	if (!(data->mlx->win))
		error(MLX_ERROR);
	create_image(data);
}
