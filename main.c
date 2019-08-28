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

int	main(int ac, const char *av[])
{
	t_data	*data;
	pid_t	window;

	if (ac < 2)
		invalid_param();
	if ((data = (t_data *)malloc(sizeof(t_data))) == NULL)
		error("Error: malloc failed in main()");
	if ((data->cam = (t_view *)malloc(sizeof(t_view))) == NULL)
		error("Error: cam malloc failed in main()");
	data->windows_count = ac - 1;
	if (data->windows_count == 2)
	{
		window = fork();
		if (window == 0)
			get_fractal_type(av[2], data);
		else
			get_fractal_type(av[1], data);
	}
	else
		get_fractal_type(av[1], data);
	init_params(data);
	mlx(data);
	return (0);
}
