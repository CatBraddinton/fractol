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

void	draw_fractal_image(char const *name)
{
	t_data 		*data;
	t_mlx		*mlx;
	t_params	*params;

	if ((data = (t_data *)malloc(sizeof(t_data))) == NULL)
		error(strerror(errno));
	get_fractal_type(name, data);
	if ((mlx = (t_mlx *)malloc(sizeof(t_mlx))) == NULL)
		error(strerror(errno));
	if ((mlx->p_mlx = mlx_init()) == NULL)
		error(strerror(errno));
	if (!(mlx->p_win = mlx_new_window(mlx->p_mlx, WIN_WIDTH, WIN_HEIGHT,
										data->name)))
		error(strerror(errno));
	if ((params = (t_params *)malloc(sizeof(t_params))) == NULL)
		error(strerror(errno));
	data->mlx = mlx;
	data->params = params;
	init_params(data);
	draw_fractals(data);
	mlx_hook(mlx->p_win, 2, 0, key_press, data);
	mlx_hook(mlx->p_win, 4, 0, mouse_press, data);
	mlx_hook(mlx->p_win, 6, 0, mouse_move, data);
	mlx_hook(mlx->p_win, 17, 0, close, data);
	mlx_loop(mlx->p_mlx);
}
