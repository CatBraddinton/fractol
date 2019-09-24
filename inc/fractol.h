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

# define MAX_ITER		500
# define TOTAL_THREADS	4

# define WIN_W		2300
# define WIN_H		1000

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
# include "../libft/libft.h"

typedef enum		e_type
{
	mandelbrot,
	julia,
	total_nb,
	invalid = -1,
}					t_type;

typedef struct		s_cnum
{
	double			re;
	double			im;
}					t_cnum;

typedef struct		s_set
{
	t_cnum			k;
	t_cnum			c;
	t_cnum			new_z;
	t_cnum			old_z;
	t_cnum			z_sqrt;
	t_cnum			diff_min_max;
	t_cnum			factor;
	t_cnum			mouse;
	t_cnum			move;
}					t_set;

typedef struct		s_mlx
{
	void			*p_mlx;
	void			*win;
	int				image_width;
	int				image_height;
	void			*img;
	char			*image;
	int				bpp;
	int				size;
	int				end;
}					t_mlx;

typedef struct		s_params
{
	int				max_iter;
	double			zoom;
	int				iter;
	double			zoom_factor;
}					t_params;

typedef struct		s_menu
{
	int				menu_width;
	int				menu_height;
	int				start_x;
	int				start_y;
	int				finish_x;
	int				finish_y;
}					t_menu;

typedef struct		s_data
{
	t_type			type;
	t_mlx			*mlx;
	t_menu			*menu;
	t_params		*params;
	t_set			*set;
//	t_cnum			threads_param[TOTAL_THREADS];
	t_cnum			min;
	t_cnum			max;
	int				**buff;
}					t_data;

void				check_input_params(int ac, char **av);
void				invalid_param(void);
void				error(char *message);

void				draw_fractal_image(char *name);








void				draw_fractals(t_data *data);
void				draw_mandelbrot_set(t_data *data);
void				draw_julia_set(t_data *data);
void				set_complex(t_cnum *n, double real, double imaginary);
void				init_params(t_data *data);
void				init_programm_architecture(t_data *data);
void				color_point(t_data *data, int **buff);
void				init_buffer(t_data *data);
int					mouse_move(int x, int y, t_data *data);
int					mouse_press(int button, int x, int y, t_data *data);
int					close(int keycode);
int					key_press(int keycode, t_data *data);

void				convert_pixels(t_cnum *n, t_data *data, int x, int y);
void				free_buff(int **buff, int size);

void				histogram_coloring(t_data *data, int **buff);
void 				zoom(t_data *data, double mouse_x, double mouse_y,
							double zoom_factor);
void	put_pixel_on_screen(t_data *data, int x, int y, int iter);

#endif
