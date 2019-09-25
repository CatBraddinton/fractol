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

void	check_input_params(int ac, char **av)
{
	int i;
	int len;

	if ((ac != 2) && (ac != 3))
		invalid_param();
	i = 1;
	while (i < ac)
	{
		len = ft_strlen(av[i]);
		if (len == 5 && (ft_strncmp(av[i], "julia", len) == 0))
			i++;
		else if (len == 10 && (ft_strncmp(av[i], "mandelbrot", len) == 0))
			i++;
		else
			invalid_param();
	}
}

void	set_complex(t_cnum *n, double real, double imaginary)
{
	n->re = real;
	n->im = imaginary;
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
