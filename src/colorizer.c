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

# include "../inc/fractol.h"

static int	get_color_value(int iter, int max_iter)
{
	t_color	color;
	double	percent;

	if (iter == max_iter)
		return (BLACK);
	percent = (double)iter / (double)max_iter;
	color.r = (int)(9 * (1 - percent) * pow(percent, 3) * 255 * iter);
	color.g = (int)(15 * pow((1 - percent), 2) * pow(percent, 2) * 255 * iter);
	color.b = (int)(8.5 * pow((1 - percent), 3) * percent * 255 * iter);
	return ((color.r << 16) | (color.g << 8) | color.b);
}

void	color_point(t_data *data, int **buff)
{
	int	x;
	int	y;
	int	color;
	int i;

	data->mlx->img = mlx_new_image(data->mlx->p_mlx, data->mlx->image_width,
										data->mlx->image_height);
	data->mlx->image = mlx_get_data_addr(data->mlx->img,
		&(data->mlx->bpp), &(data->mlx->size), &(data->mlx->end));
	y = -1;
	while (++y < data->mlx->image_height && (x = -1))
		while (++x < data->mlx->image_width)
		{
			color = get_color_value(buff[y][x], data->params->max_iter);
			i = (x * data->mlx->bpp / 8) + (y * data->mlx->size);
			data->mlx->image[i] = color;
			data->mlx->image[++i] = color >> 8;
			data->mlx->image[++i] = color >> 16;
			data->mlx->image[++i] = 0;
		}
		mlx_put_image_to_window(data->mlx->p_mlx, data->mlx->win,
			data->mlx->img, 0, 0);
}

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
