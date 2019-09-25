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
	ft_putendl("Tricorn ----------> [tricorn]");
	exit(EXIT_FAILURE);
}

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
		else if (len == 7 && (ft_strncmp(av[i], "tricorn", len) == 0))
				i++;
		else
			invalid_param();
	}
}
