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
# define WIN_WIDTH		1920
# define WIN_HEIGHT		1080

# include <stdio.h>
# include <math.h>
# include <mlx.h>

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

typedef struct		s_data
{
	int				windowns_nb;
	int				fractal_type1;
	int				fractal_type2;
	t_mlx			mlx_data;
}					t_data;

void				init_data(t_data *all);
void				error(char *message);
void				invalid_param(void);
void				get_fractal_types(t_data *all, int ac, char *av[]);

void				draw(t_data *all);
void				draw_mandelbrot_set(t_data *all);
void				draw_sierpinskie_triangle(t_data *all);
void				draw_julia_set(t_data *all);

#endif
