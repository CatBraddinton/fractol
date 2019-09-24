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

	if ((ac != 2) && (ac != 3))
		invalid_param();
	i = 1;
	while (i < ac)
		if ((ft_strncmp(av[i], "julia", ft_strlen(av[i]))) == 0)
			i++;
		else if ((ft_strncmp(av[i], "mandelbrot", ft_strlen(av[i]))) == 0)
			i++;
		else
			invalid_param();
}

void	get_fractal_type(t_type *type, char *input)
{
	if ((ft_strncmp(input, "julia", ft_strlen(input))) == 0)
		*type = julia;
	else if ((ft_strncmp(input, "mandelbrot", ft_strlen(input))) == 0)
		*type = mandelbrot;
	else
		invalid_param();
}

void	free_buff(int **buff, int size)
{
	int i;

	i = 0;
	while (i < size)
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

void	init_buffer(t_data *data)
{
	int i;

	i = -1;
	if (!(data->buff = (int **)malloc(data->mlx->image_height * sizeof(int *))))
		error("malloc error");
	while (++i < data->mlx->image_height)
	{
		if (!(data->buff[i] = (int *)malloc(data->mlx->image_width * sizeof(int))))
			error("malloc error");
		ft_memset(data->buff[i], 0, data->mlx->image_width);
	}
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
	data->params->iter = 0;
	data->params->zoom_factor = 0;
	if ((data->set = (t_set *)malloc(sizeof(t_set))) == NULL)
		error(strerror(errno));
	set_complex(&(data->set->k), 0.4, -0.6);
}
