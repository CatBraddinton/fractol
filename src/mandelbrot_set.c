/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot_set.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdudko <kdudko@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 20:18:55 by kdudko            #+#    #+#             */
/*   Updated: 2019/08/14 20:18:58 by kdudko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

void	draw_mandelbrot_set(t_data *all)
{
	if ((all->mlx_data.p_window = mlx_new_window(all->mlx_data.p_mlx,
		WIN_WIDTH, WIN_HEIGHT, "Mandelbrot Set")) == NULL)
		error("Error: mlx failed to open new window in draw_mandelbrot_set()");
}
