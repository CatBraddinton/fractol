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

#include "inc/fractol.h"

int	main(int ac, char const *av[])
{
	pid_t	 window;

	errno = 0;
	if (ac < 2)
		invalid_param();
	if (ac == 3)
	{
		window = fork();
		if (window == 0)
			draw_fractal_image(av[2]);
		else
			draw_fractal_image(av[1]);
	}
	else if (ac == 2)
		draw_fractal_image(av[1]);
	return (0);
}
