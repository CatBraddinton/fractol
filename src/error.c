/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdudko <kdudko@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 20:14:38 by kdudko            #+#    #+#             */
/*   Updated: 2019/08/13 20:14:40 by kdudko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

void	error(char *message)
{
	perror(message);
	exit(EXIT_FAILURE);
}

void	invalid_param(void)
{
	ft_putendl("usage: ./fractol [fractal_name] [fractal_name2]");
	ft_putendl("\navailable fractals:");
	ft_putendl("Julia set --------> [julia]");
	ft_putendl("Mandelbrot set ---> [mandelbrot]");
	exit(EXIT_FAILURE);
}
