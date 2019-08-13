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
	ft_putendl("2 - Mendelbrot Set");
	exit(EXIT_FAILURE);
}

void	get_fractal_types(t_data *all, int ac, char *av[])
{
	if ((ac != 2 && ac != 3) || (ac == 2 && !av[1]) ||
		(ac == 3 && (!av[1] || !av[2])))
		invalid_param();
	all->windowns_nb = ac - 1;
	all->fractal_type1 = ft_atoi(av[1]);
	if (all->fractal_type1 != 1 && all->fractal_type1 != 2)
		invalid_param();
	if (ac == 3)
	{
		all->fractal_type2 = ft_atoi(av[2]);
		if (all->fractal_type2 != 1 && all->fractal_type2 != 2)
			invalid_param();
	}
}
