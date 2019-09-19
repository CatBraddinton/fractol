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
	if ((data->mlx = (t_mlx *)malloc(sizeof(t_mlx))) == NULL)
		error(strerror(errno));
	if ((data->menu = (t_menu *)malloc(sizeof(t_menu))) == NULL)
		error(strerror(errno));
	if ((data->params = (t_params *)malloc(sizeof(t_params))) == NULL)
		error(strerror(errno));
	if ((data->set = (t_set *)malloc(sizeof(t_set))) == NULL)
		error(strerror(errno));
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
