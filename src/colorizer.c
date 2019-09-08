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
	color.r = (int)(9 * (1 - percent) * pow(percent, 3) * 255);
	color.g = (int)(15 * pow((1 - percent), 2) * pow(percent, 2) * 255);
	color.b = (int)(8.5 * pow((1 - percent), 3) * percent * 255);
	return ((color.r << 16) | (color.g << 8) | color.b);
}

void	color_point(t_data *data, int **buff)
{
	int	x;
	int	y;
	int	color;
	int i;

	data->mlx->p_img = mlx_new_image(data->mlx->p_mlx, WIDTH, HEIGHT);
	data->mlx->img_buffer = mlx_get_data_addr(data->mlx->p_img,
		&(data->mlx->bpp), &(data->mlx->size), &(data->mlx->end));
	y = -1;
	while (++y < HEIGHT && (x = -1))
		while (++x < WIDTH)
		{
			color = get_color_value(buff[y][x], data->params->max_iter);
			i = (x * data->mlx->bpp / 8) + (y * data->mlx->size);
			data->mlx->img_buffer[i] = color;
			data->mlx->img_buffer[++i] = color >> 8;
			data->mlx->img_buffer[++i] = color >> 16;
			data->mlx->img_buffer[++i] = 0;
		}
	mlx_put_image_to_window(data->mlx->p_mlx, data->mlx->p_win,
		data->mlx->p_img, 0, 0);
}
