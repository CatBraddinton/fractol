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
#include "../inc/mandelbrot_and_julia.h"

// int	init_set(t_complex *n, double real, double imaginary, int mode)
// {
// 	if (mode == MODE_SET)
// 	{
// 		n->r = real;
// 		n->im = imaginary;
// 	}
// 	else if (mode == MODE_POW)
// 	{
// 		n->r = pow(real, POWER);
// 		n->im = pow(imaginary, POWER);
// 	}
// 	else if (mode == MODE_BOOL)
// 	{
// 		n->r = pow(real, POWER);
// 		n->im = pow(imaginary, POWER);
// 		if (n->r + n->im <= 4.0)
// 			return (1);
// 	}
// 	return (0);
// }
//
void	draw_fractals(t_data *data)
{
	void (*draw_fractal[TOTAL_NB]) (t_data *data);

	draw_fractal[0] = draw_julia_set;
	draw_fractal[1] = draw_mandelbrot_set;
	(*draw_fractal[data->type - 1])(data);
}

void	init_params(t_data *data)
{
	data->mlx->bpp = 0;
	data->mlx->size = 0;
	data->mlx->end = 0;
	data->params->max_iter = MAX_ITER;
	data->params->zoom = 1.0;
	data->params->mouse_x = 0;
	data->params->mouse_y = 0;
	data->params->iter = 0;
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
	if (!(mlx->p_win = mlx_new_window(mlx->p_mlx, WIDTH, HEIGHT, data->name)))
		error(strerror(errno));
	if ((params = (t_params *)malloc(sizeof(t_params))) == NULL)
		error(strerror(errno));
	data->mlx = mlx;
	data->params = params;
	init_params(data);
	draw_fractals(data);
	// mlx_hook(data->p_window, 2, 0, key_press, data);
	// mlx_hook(data->p_window, 4, 0, mouse_press, data);
	// mlx_hook(data->p_window, 6, 0, mouse_move, data);
	mlx_hook(mlx->p_win, 17, 0, close, data);
	mlx_loop(mlx->p_mlx);
}
