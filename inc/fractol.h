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
# define WIN_WIDTH		2580
# define WIN_HEIGHT		1430
# define IMG_WIDTH		2580
# define IMG_HEIGHT		1430

# include <stdio.h>
# include <math.h>
# include <mlx.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>

# include "hooks.h"

typedef struct		s_color
{
	int				red;
	int				green;
	int				blue;
}					t_color;


typedef struct		s_mlx
{
	void			*p_mlx;
	void			*p_window;
	void			*p_image;
	char			*img_buffer;
	int				bpp;
	int				size_line;
	int				endian;
}					t_mlx;

typedef struct		s_data
{
	t_mlx			*mlx_data;
	int				windows_count;
	int				type;
	int				win_width;
	int				win_height;
	int				img_width;
	int				img_height;
	t_color			p_color;
}					t_data;

void				error(char *message);
void				invalid_param(void);
void				init_data(t_data *data, char *input);
int					get_fractal_type(char *input);
void				count_fractal(t_data *data);
int					close(int keycode);
int					key_press(int keycode, t_data *data);
void				draw_sierpinskie_triangle(t_data *data);
void				draw_julia_set(t_data *data);

#endif
