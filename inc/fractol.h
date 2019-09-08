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

# define TOTAL_NB		2

# define WIDTH			1980
# define HEIGHT			1080
# define MAX_ITER		500

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

typedef struct		s_cnum
{
	double			re;
	double			im;
}					t_cnum;

typedef struct		s_set
{
	t_cnum			delta;
	t_cnum			k;
	t_cnum			c;
	t_cnum			new_z;
	t_cnum			old_z;
	t_cnum			z_sqrt;
}					t_set;

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
	double			mouse_x;
	double			mouse_y;
	double			move_x;
	double			move_y;
	int				iter;
	double			center_x;
	double			center_y;
	double			scale_x;
	double			scale_y;
	double			transf_x;
	double			transf_y;
}					t_params;

typedef struct		s_data
{
	char			*name;
	int				type;
	t_mlx			*mlx;
	t_params		*params;
	t_set			set;
	int				**buff;
}					t_data;

void				error(char *message);
void				invalid_param(void);
void				draw_fractal_image(char const *name);
void				get_fractal_type(const char *input, t_data *data);
// void				init_params(t_data *data);
void				draw_fractals(t_data *data);
void				draw_mandelbrot_set(t_data *data);
void				draw_julia_set(t_data *data);
void				set_complex(t_cnum *n, double real, double imaginary);
// void				init_cam(t_data *data);
// void				mlx(t_data *data);
void				color_point(t_data *data, int **buff);
void	init_buffer(t_data *data);
int					mouse_move(int x, int y, t_data *data);
// int					mouse_press(int button, int x, int y, t_data *data);
int					close(int keycode);
int					key_press(int keycode, t_data *data);
// int					init_set(t_complex *n, double real, double imaginary, int mode);

void	convert_pixels(t_cnum *n, t_data *data, int x, int y);
void	free_buff(int **buff);
void	count_points(t_data *data, t_cnum complex);
#endif
