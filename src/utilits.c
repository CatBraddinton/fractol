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

void	free_buff(int **buff)
{
	int i;

	i = 0;
	while (i < HEIGHT)
	{
		free(buff[i]);
		i++;
	}
	free(buff);
}

void	set_complex(t_cnum *n, double real, double imaginary)
{
	n->re = real;
	n->im = imaginary;
}

void	draw_fractals(t_data *data)
{
	void (*draw_fractal[TOTAL_NB]) (t_data *data);

	draw_fractal[0] = draw_julia_set;
	draw_fractal[1] = draw_mandelbrot_set;
	(*draw_fractal[data->type - 1])(data);
}

void	init_buffer(t_data *data)
{
	int i;

	i = -1;
	if ((data->buff = (int **)malloc(HEIGHT * sizeof(int *))) == NULL)
		error("malloc error");
	while (++i < HEIGHT)
		if ((data->buff[i] = (int *)malloc(WIDTH * sizeof(int))) == NULL)
			error("malloc error");
}

void	init_params(t_data *data)
{
	data->im_offset_x = 0;
	data->im_offset_y = 0;
	data->re_min = -2.5;
	data->im_min = -1.0;
	data->im_max = 1.0;
	data->re_max = 1.0;
	data->mlx->bpp = 0;
	data->mlx->size = 0;
	data->mlx->end = 0;
	data->params->max_iter = MAX_ITER;
	data->params->zoom = 0.0;
	data->params->mouse_x = 0;
	data->params->mouse_y = 0;
	data->params->move_x = 0.0;
	data->params->move_y = 0.0;
	data->params->iter = 0;
	data->params->center_x = WIDTH / 2;
	data->params->center_y = HEIGHT / 2;
	data->spacing = (fabs(data->re_min) + data->re_max) / WIDTH;
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
