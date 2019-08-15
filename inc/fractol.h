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

# include "hooks.h"

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

void				error(char *message);
void				invalid_param(void);
int					get_fractal_type(char *input);
void				count_fractal(int type);
int					close(int keycode);
int					close_window(t_mlx *data);
int					key_press(int keycode, t_mlx *data);
void				draw_mandelbrot_set(void);
void				draw_sierpinskie_triangle(void);
void				draw_julia_set(void);

#endif
