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


# define MAX_ITER			30

# define TOTAL_THREADS		4

# define IMG_W				1920
# define IMG_H				1200
# define MENU_W				600
# define MENU_H				1200

# define SIDE_PANEL_IMGS	3
# define SIDE_PANEL_IMG_W	600
# define SIDE_PANEL_IMG_H	400

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
	double			zoom_factor;
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
	t_cnum			m_min;
	t_cnum			m_max;
	t_cnum			j_k;
	double			iter;
}					t_side_panel;

typedef struct		s_data
{
	t_type			type;
	t_mlx			*mlx;
	t_side_panel	*small_img;
	t_params		*params;
	t_cnum			min;
	t_cnum			max;
	int				julia_mouse_lock;
	pthread_mutex_t lock;
	int				i;
	int				x[TOTAL_THREADS];
	int				y[TOTAL_THREADS];
	double			iter[TOTAL_THREADS];
}					t_data;

void				check_input_params(int ac, char **av);
void				invalid_param(void);
void				error(char *message);

void				draw_fractal_image(char *name);
int					expose_hook(t_data *data);
void				count_points(t_data *data, t_set *set);
void				init_mlx_window(t_data *data, char *name);
void				draw_burning_ship_fractal(t_data *data, int x, int y, int i);
void				draw_tricorn_fractal(t_data *data, int x, int y, int i);
void				init_extremums(t_data *data);
void				draw_fractals(t_data *data);
void				draw_mandelbrot_set(t_data *data, int x, int y, int i);
void				draw_julia_set(t_data *data, int x, int y, int i);
void				set_complex(t_cnum *n, double real, double imaginary);
void				init_params(t_data *data);
void				init_programm_architecture(t_data *data);
void				color_point(t_data *data, int x, int y, int n);
void				init_buffer(t_data *data);
int					julia_motion(int x, int y, t_data *data);
int					mouse_hook(int button, int x, int y, t_data *data);

int					key_press(int keycode, t_data *data);
void				convert_pixels(t_cnum *n, t_data *data, int x, int y);
void				histogram_coloring(t_data *data, int **buff);
void 				zoom(t_data *data, double mouse_x, double mouse_y,
							double zoom_factor);
void				put_pixel_on_screen(t_data *data, int x, int y, int iter);
void				*draw_app_menu(void *param);
double				iter_to_double(t_cnum n, int iter);
void				draw_menu_julia_set(t_data *data, int i);
void				draw_menu_mandelbrot_set(t_data *data, int i);
void				draw_menu_burning_ship_fractal(t_data *data, int i);
void				draw_menu_tricorn_fractal(t_data *data, int i);
void				count_menu_points(t_data *data, t_set *set, int i);
void				color_menu_point(t_data *data, int x, int y, int n);
#endif
