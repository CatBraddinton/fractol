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

static int	get_color_value(double iter, int max_iter)
{
	t_color	color;

	if (iter == max_iter)
		return (BLACK);
	color.r = iter * 13;
	color.g = iter * 198;
	color.b = iter * 56;
	return ((color.r << 16) | (color.g << 8) | color.b);
}

void		color_point(t_data *data, int x, int y, int n)
{
	unsigned int	color;
	int				rgb;

	rgb = get_color_value(data->iter[n], data->params->max_iter);
	color = mlx_get_color_value(data->mlx->p_mlx, rgb);
	((unsigned int*)data->mlx->image)[y * IMG_W + x] = color;
}

void		color_menu_point(t_data *data, int x, int y, int n)
{
	unsigned int	color;
	int				rgb;

	rgb = get_color_value(data->small_img[n].iter, data->params->max_iter);
	color = mlx_get_color_value(data->mlx->p_mlx, rgb);
	((unsigned int*)data->small_img[n].m_image)[y * SIDE_PANEL_IMG_W + x]
		= color;
}

/*
void	histogram_coloring_step_2(t_data *data, int **buff, int *iters_pp)
{
	int x;
	int	y;
	int i;

	x = -1;
	y = -1;
	i = 0;
	ft_memset(iters_pp, 0, data->params->max_iter);
	while (++x < data->mlx->image_width)
		while (++y < data->mlx->image_height)
		{
			i = buff[y][x];
			iters_pp[i] += 1;
		}
}

int		histogram_coloring_step_3(int *iters_pp, int size)
{
	int	total;
	int i;

	total = 0;
	i = -1;
	while (++i < size)
		total += iters_pp[i];
	return (total);
}

void	histogram_coloring_step_4(t_data *data, int **buff, int *iters_pp, int **hue)
{
	int x;
	int y;
	int i;
	int iter;

	x = -1;
	y = -1;
	i = -1;
	iter = 0;
	while (++x < data->mlx->image_width)
		while (++y < data->mlx->image_height)
		{
			iter = buff[y][x];
			while (++i < iter)
				hue[y][x] += iters_pp[i];
		}
}

void	histogram_coloring(t_data *data, int **buff)
{
	int			*iters_pp;
	long long	total;
	int			**hue;
	int			i;

	i = -1;
	if (!(iters_pp = (int *)malloc(data->params->max_iter * sizeof(int))))
		error(strerror(errno));
	histogram_coloring_step_2(data, buff, iters_pp);
	total = histogram_coloring_step_3(iters_pp, data->params->max_iter);
	if (!(hue = (int **)malloc(data->mlx->image_height * sizeof(int *))))
		error(strerror(errno));
	while (++i < data->mlx->image_height)
	{
		if (!(hue[i] = (int *)malloc(data->mlx->image_width * sizeof(int))))
			error(strerror(errno));
		ft_memset(hue[i], 0, data->mlx->image_width);
	}
	histogram_coloring_step_4(data, buff, iters_pp, hue);
}
*/
