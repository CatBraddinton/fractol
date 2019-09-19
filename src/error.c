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
	ft_putendl("usage: ./fractol param");
	ft_putendl("\navailable params:");
	ft_putendl("Julia");
	ft_putendl("Mandelbrot");
	exit(EXIT_FAILURE);
}

void	get_fractal_type(t_type *type, char *input)
{
	if ((ft_strncmp("Julia", input, ft_strlen("Julia"))) == 0)
		*type = julia;
	else if ((ft_strncmp("Mandelbrot", input, ft_strlen("Mandelbrot"))) == 0)
		*type = mandelbrot;
	else
		invalid_param();
}
