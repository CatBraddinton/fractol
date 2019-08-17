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
	t_data	*all_data;
	pid_t	window;

	if (ac < 2)
		invalid_param();
	if ((all_data = (t_data *)malloc(sizeof(t_data))) == NULL)
		error("Error: malloc failed in main()");
	all_data->windows_count = ac - 1;
	if (all_data->windows_count == 2)
	{
		window = fork();
		if (window == 0)
			init_data(all_data, av[2]);
		else
			init_data(all_data, av[1]);
	}
	else
		init_data(all_data, av[1]);
	count_fractal(all_data);
	return (0);
}
