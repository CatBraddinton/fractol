#include "../inc/mandelbrot_and_julia.h"



// int julia_motion(int x, int y, t_set *set)
// {
// 	init_set(&(set->k), 4 * ((double)x / WIDTH - 0.5),
// 		4 * ((double)(HEIGHT - y) / HEIGHT - 0.5), MODE_SET);
// 	return (0);
// }
//
// static void	draw_mandelbrot(t_data *data, t_set *set)
// {
// 	int x;
// 	int y;
//
// 	y = -1;
// 	while (++y < HEIGHT)
// 	{
// 		set->c.im = set->max.im - y * set->factor.im;
// 		x = -1;
// 		while (++x < WIDTH)
// 		{
// 			set->c.r = set->min.r + x * set->factor.r;
// 			init_set(&(set->z), set->c.r, set->c.im, MODE_SET);
// 			data->iter = 0;
// 			while (data->iter < data->max_iter
// 				&& init_set(&(set->pwr), set->z.r, set->z.im, MODE_BOOL))
// 			{
// 				set->temp = 2.0 * set->z.r * set->z.im + set->c.im;
// 				init_set(&(set->z), (set->pwr.r - set->pwr.im + set->c.r),
// 				set->temp, MODE_SET);
// 				data->iter++;
// 			}
// 			set_color_to_point(data, x, y);
// 		}
// 	}
// }
//
// void		draw_mandelbrot_julia(t_data *data)
// {
// 	t_set	set;
//
// 	if (!(data->p_image = mlx_new_image(data->p_mlx, WIDTH, HEIGHT)))
// 		error("Error: mlx failed to create new image in mlx()");
// 	if ((data->img_buffer = mlx_get_data_addr(data->p_image, &(data->bpp),
// 		&(data->size_line), &(data->endian))) == NULL)
// 		error("Error: mlx failed to return information about created image\
// 		in draw_mandelbrot_julia()");
// 	init_set(&(set.min), -2.0, -2.0, MODE_SET);
// 	init_set(&(set.max), 2.0, 2.0, MODE_SET);
// 	init_set(&(set.factor), (set.max.r - set.min.r) / WIDTH / data->change->zoom,
// 			(set.max.im - set.min.im) / HEIGHT / data->change->zoom, MODE_SET);
// 	if (data->type == 1)
// 	{
// 		if (data->mouse_x == 0 && data->mouse_y == 0)
// 			init_set(&(set.k), -0.4, 0.6, MODE_SET);
// 		else
// 	 		julia_motion(data->mouse_x, data->mouse_y, &set);
// 		draw_julia(data, &set);
// 	}
// 	else if (data->type == 2)
// 		draw_mandelbrot(data, &set);
// 	mlx_put_image_to_window(data->p_mlx, data->p_window, data->p_image,	0, 0);
// }
