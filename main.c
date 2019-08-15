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
	int type;

	if (ac < 2)
		invalid_param();
	type = get_fractal_type(av[1]);
	count_fractal(type);
	return (0);
}
