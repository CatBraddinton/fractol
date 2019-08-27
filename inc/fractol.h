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
# define SIERPINSKI		3

# define TOTAL_NB		3
# define WIDTH			1500
# define HEIGHT			1500

# include <stdio.h>
# include <math.h>
# include <mlx.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>

# include "hooks.h"
# include "colorize_it.h"

typedef struct		s_view
{
	double			zoom;
	int				offset_x;
	int				offset_y;
	int				center_x;
	int				center_y;
	int				origin_x;
	int				origin_y;
}					t_view;

typedef struct		s_data
{
	int				windows_count;
	char			*name;
	int				type;
	void			*p_mlx;
	void			*p_window;
	void			*p_image;
	char			*img_buffer;
	int				bpp;
	int				size_line;
	int				endian;
	double			zoom;
	int				pos_left;
	int				pos_right;
	int				pos_up;
	int				pos_down;
	int				max_iter;
	int				iter;
}					t_data;

void				error(char *message);
void				invalid_param(void);
void				get_fractal_type(const char *input, t_data *data);
void				count_fractal(t_data *data);
int					close(int keycode);
int					key_press(int keycode, t_data *data);
void				init_cam(t_data *data);
void				mlx(t_data *data);
void				set_color_to_point(t_data *data, int x, int y);

#endif
