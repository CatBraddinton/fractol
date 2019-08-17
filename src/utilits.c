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
#include "../inc/mandelbrot_set.h"

void	init_data(t_data *all_data, char *input)
{
	if ((all_data->mlx_data = (t_mlx *)malloc(sizeof(t_mlx))) == NULL)
		error("Error: malloc failed in init_data()");
	all_data->type = get_fractal_type(input);
	all_data->win_width = WIN_WIDTH / all_data->windows_count;
	all_data->win_height = WIN_HEIGHT / all_data->windows_count;
	all_data->img_width = IMG_WIDTH / all_data->windows_count;
	all_data->img_height = IMG_HEIGHT / all_data->windows_count;
	all_data->mlx_data->p_mlx = NULL;
	all_data->mlx_data->p_window = NULL;
	all_data->mlx_data->p_image = NULL;
	all_data->mlx_data->img_buffer = NULL;
	all_data->mlx_data->bpp = 0;
	all_data->mlx_data->size_line = 0;
	all_data->mlx_data->endian = 0;
}

void	count_fractal(t_data *data)
{
	void (*draw_fractal[TOTAL_NB + 1]) (t_data *data);

	draw_fractal[0] = NULL;
	draw_fractal[JULIA] = draw_julia_set;
	draw_fractal[MANDELBROT] = draw_mandelbrot_set;
	draw_fractal[SIERPINSKI] = draw_sierpinskie_triangle;
	(*draw_fractal[data->type])(data);
}
