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

void	count_fractal(int type)
{
	void (*draw_fractal[TOTAL_NB + 1]) (void);

	draw_fractal[0] = NULL;
	draw_fractal[JULIA] = draw_julia_set;
	draw_fractal[MANDELBROT] = draw_mandelbrot_set;
	draw_fractal[SIERPINSKI] = draw_sierpinskie_triangle;
	(*draw_fractal[type])();
}
