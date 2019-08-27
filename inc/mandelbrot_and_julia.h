/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot_and_julia.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdudko <kdudko@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 05:58:15 by kdudko            #+#    #+#             */
/*   Updated: 2019/08/27 05:58:19 by kdudko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MANDELBROT_AND_JULIA_H
# define MANDELBROT_AND_JULIA_H

# define MODE_SET	1
# define MODE_POW	2
# define MODE_BOOL	3

# define POWER		2.0

# include "fractol.h"

typedef struct		s_complex
{
	double			r;
	double			im;
}					t_complex;

typedef struct		s_mandelbrot
{
	t_complex		min;
	t_complex		max;
	t_complex		factor;
	t_complex		cmlx;
	t_complex		z;
	t_complex		pwr;
	double			temp;
}					t_mandelbrot;

 void				draw_mandelbrot_set(t_data *data);
 void				draw_julia_set(t_data *data);
 
#endif
