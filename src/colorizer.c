/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colorizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdudko <kdudko@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 19:40:53 by kdudko            #+#    #+#             */
/*   Updated: 2019/08/20 19:40:55 by kdudko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

int		get_color_value_v1(int iter, int max_iter)
{
	t_color	color;
	double	percent;

	if (iter == max_iter)
		return (BLACK);
	percent = iter / (double)max_iter;
	color.r = (int)(9 * (1 - percent) * pow(percent, 3) * 255);
	color.g = (int)(15 * pow((1 - percent), 2) * pow(percent, 2) * 255);
	color.b = (int)(8.5 * pow((1 - percent), 3) * percent * 255);
	return ((color.r << 16) | (color.g << 8) | color.b);
}

void	color_point(t_data *data, int x, int y, int n)
{
	unsigned int	color;
	int				rgb;

	if (data->color_style == 1)
		rgb = get_color_value_v1(data->iter[n], data->params->max_iter);
	if (data->color_style == 2)
		rgb = get_color_value_v1(data->iter[n], data->params->max_iter);
	color = mlx_get_color_value(data->mlx->p_mlx, rgb);
	((unsigned int*)data->mlx->image)[y * IMG_W + x] = color;
}

void	color_menu_point(t_data *data, int x, int y, int n)
{
	unsigned int	col;
	int				rgb;

	rgb = get_color_value_v1(data->small_img[n].iter, data->params->max_iter);
	col = mlx_get_color_value(data->mlx->p_mlx, rgb);
	((unsigned int*)data->small_img[n].m_image)[y * SIDE_PANEL_IMG_W + x] = col;
}
