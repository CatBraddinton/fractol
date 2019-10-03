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

# define MALLOK_ERROR 	"Malloc failed to allocate enought memory."
# define TYPE_ERROR 	"Fractal type value is invalid."
# define MLX_ERROR		"MLX LIB failure."
# define PTHREAD_ERROR	"Pthread failed to create new thread."

# define MAX_ITER			80

# define TOTAL_THREADS		4

# define IMG_W				1920
# define IMG_H				1220
# define MENU_W				600
# define MENU_H				1240

# include <stdio.h>
# include <math.h>
# include <mlx.h>
# include <pthread.h>
# include <sys/types.h>
# include <sys/errno.h>

# include "hooks.h"
# include "colorize_it.h"
# include "../libft/inc/libft.h"
# include "../libft/inc/my_cg_lib.h"
# include "side_panel.h"

typedef enum		e_type
{
	mandelbrot,
	julia,
	tricorn,
	burning_ship,
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
	int				iter;
	double			iter_double;
	t_cnum			k;
	t_cnum			c;
	t_cnum			new_z;
	t_cnum			old_z;
	t_cnum			z_sqrt;
	t_cnum			f;

}					t_set;

typedef struct		s_mlx
{
	void			*p_mlx;
	void			*win;
	int				win_w;
	int				win_h;
	int				im_w;
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
	double			zoom_f;
	t_cnum			mouse;
	t_cnum			move;
	t_cnum			center;
	t_cnum			julia_k;
}					t_params;

typedef struct		s_side_panel
{
	void			*m_img;
	char			*m_image;
	int				bpp;
	int				size;
	int				end;
	t_type			type;
	int				iter;
	t_type			mem;
	int				y_s;
}					t_side_panel;

typedef struct		s_data
{
	t_type			type;
	t_mlx			*mlx;
	t_side_panel	*img;
	t_params		*params;
	t_cnum			min;
	t_cnum			max;
	pthread_mutex_t lock;
	int				i;
	int				x[TOTAL_THREADS];
	int				y[TOTAL_THREADS];
	int				iter[TOTAL_THREADS];
	int				mouse_left_key;
	int				julia_mouse_lock;
	int				color_style;
	int				show_side_panel;
}					t_data;

void				check_input_params(int ac, char **av);
void				invalid_param(void);
void				error(char *message);

void				draw_fractal_image(char *name);
int					expose_hook(t_data *data);
void				count_points(t_data *data, t_set *set);

void				init_extremums(t_data *data);
void				draw_fractals(t_data *data);

void				set_complex(t_cnum *n, double real, double imaginary);
void				init_params(t_data *data);
void				init_programm_architecture(t_data *data);
void				color_point(t_data *data, int x, int y, int n);
void				init_buffer(t_data *data);
int					julia_motion(int x, int y, t_data *data);
int					mouse_hook(int button, int x, int y, t_data *data);
int					key_press(int keycode, t_data *data);
void				convert_pixels(t_cnum *n, t_data *data, int x, int y);
void				put_pixel_on_screen(t_data *data, int x, int y, int iter);

void				count_menu_points(t_data *data, t_set *set, int i);
void				color_menu_point(t_data *data, int x, int y, int n);
void				init_params(t_data *data);
void				threads_counting(t_data *data);

void				zoom_image(int button, int x, int y, t_data *data);
int					is_in_mandelbrot_set(double x, double y);

#endif
