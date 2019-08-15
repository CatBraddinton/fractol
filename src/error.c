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

#include "../libft/libft.h"
#include "../inc/fractol.h"

void	error(char *message)
{
	ft_putendl(message);
	exit(EXIT_FAILURE);
}

/*
** Function that prints usage of a program if:
** Program was executed without specifing param value.
** Param value is invalid.
*/

void	invalid_param(void)
{
	ft_putendl("usage: ./fractol param");
	ft_putendl("\navailable params:");
	ft_putendl("1 - Julia Set");
	ft_putendl("2 - Mandelbrot Set");
	ft_putendl("3 - Sierpinski Triangle");
	exit(EXIT_FAILURE);
}

int		get_fractal_type(char *input)
{
	int type;

	type = ft_atoi(input);
	if (type != JULIA && type != MANDELBROT && type != SIERPINSKI)
		invalid_param();
	return (type);
}
