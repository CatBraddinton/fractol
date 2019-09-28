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

int	main(int ac, char *av[])
{
	pid_t	 id;

	check_input_params(ac, av);
	if (ac == 3)
	{
		id = fork();
		if (id == 0)
			draw_fractal_image(av[2]);
	}
	draw_fractal_image(av[1]);
	return (0);
}
