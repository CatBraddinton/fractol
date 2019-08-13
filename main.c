/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdudko <kdudko@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 20:10:57 by kdudko            #+#    #+#             */
/*   Updated: 2019/08/13 20:11:04 by kdudko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "inc/fractol.h"

int	main(int ac, char *av[])
{
	t_data	all;

	get_fractal_types(&all, ac, av);
	ft_putnbr(all.windowns_nb);
	ft_putchar('\n');
	ft_putnbr(all.fractal_type1);
	ft_putchar('\n');
	ft_putnbr(all.fractal_type2);
	ft_putchar('\n');
	return (0);
}
