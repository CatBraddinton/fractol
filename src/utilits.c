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

void	init_data(t_data *all)
{
	all->windowns_nb = 0;
	all->fractal_type1 = 0;
	all->fractal_type2 = 0;
	all->mlx_data.p_mlx = NULL;
	all->mlx_data.p_window = NULL;
	all->mlx_data.p_image = NULL;
	all->mlx_data.img_buffer = NULL;
	all->mlx_data.bpp = 0;
	all->mlx_data.size_line = 0;
	all->mlx_data.endian = 0;
}

void	draw(t_data *all)
{
	void (*draw_fractal[TOTAL_NB + 1]) (t_data *all);

	draw_fractal[0] = NULL;
	draw_fractal[JULIA] = draw_julia_set;
	draw_fractal[MANDELBROT] = draw_mandelbrot_set;
	draw_fractal[SIERPINSKI] = draw_sierpinskie_triangle;
	if (all->fractal_type1 > 0 && all->fractal_type1 <= TOTAL_NB)
		(*draw_fractal[all->fractal_type1]) (all);
	if (all->fractal_type2 > 0 && all->fractal_type2 <= TOTAL_NB)
		(*draw_fractal[all->fractal_type2]) (all);
}
