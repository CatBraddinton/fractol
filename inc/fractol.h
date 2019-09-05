/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdudko <kdudko@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 20:11:35 by kdudko            #+#    #+#             */
/*   Updated: 2019/08/13 20:11:36 by kdudko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# define JULIA			1
# define MANDELBROT		2

# define WIDTH			2048
# define HEIGHT			1080
# define MAX_ITER		150

# include <stdio.h>
# include <math.h>
# include <mlx.h>
# include <pthread.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/errno.h>
# include "hooks.h"
# include "colorize_it.h"

typedef struct		s_mlx
{
	void			*p_mlx;
	void			*p_win;
	void			*p_img;
	char			*img_buffer;
	int				bpp;
	int				size;
	int				end;
}					t_mlx;

typedef struct		s_params
{
	int				max_iter;
	double			zoom;
	int				mouse_x;
	int				mouse_y;
	int				iter;
}					t_params;

typedef struct		s_data
{
	char			*name;
	int				type;
	t_mlx			*mlx;
	t_params		*params;
}					t_data;

void				error(char *message);
void				invalid_param(void);
void				draw_fractal_image(char const *name);
void				get_fractal_type(const char *input, t_data *data);
// void				init_params(t_data *data);
void				draw_fractals(t_data *data);
// void				init_cam(t_data *data);
// void				mlx(t_data *data);
// void				set_color_to_point(t_data *data, int x, int y);
// int					key_press(int keycode, t_data *data);
// int					mouse_move(int x, int y, t_data *data);
// int					mouse_press(int button, int x, int y, t_data *data);
// int					close(int keycode);
// int					init_set(t_complex *n, double real, double imaginary, int mode);
#endif
