/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdudko <kdudko@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 23:35:20 by kdudko            #+#    #+#             */
/*   Updated: 2019/09/27 23:35:21 by kdudko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

void	zoom(t_data *data, double mouse_x, double mouse_y, double zoom_factor)
{
	double interpolation;

	interpolation = 1.0 / zoom_factor;
	data->min.re = interpolate(mouse_x, data->min.re, interpolation);
	data->min.im = interpolate(mouse_y, data->min.im, interpolation);
	data->max.re = interpolate(mouse_x, data->max.re, interpolation);
	data->max.im = interpolate(mouse_y, data->max.im, interpolation);
}
