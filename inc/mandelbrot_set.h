/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot_set.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdudko <kdudko@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 16:01:03 by kdudko            #+#    #+#             */
/*   Updated: 2019/08/17 16:01:04 by kdudko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MANDELBROT_SET_H
# define MANDELBROT_SET_H

# define MODE_SET	1
# define MODE_POW	2
# define MODE_BOOL	3

# define POWER		2.0

# include "fractol.h"
# include "colorize_it.h"

typedef struct		s_complex
{
	double			r;
	double			im;
}					t_complex;

typedef struct		s_mandelbrot
{
	int				max_iter;
	int				iter;
	t_complex		min;
	t_complex		max;
	t_complex		factor;
	t_complex		cmlx;
	t_complex		z;
	t_complex		pwr;
	double			temp;
}					t_mandelbrot;

void				draw_mandelbrot_set(t_data *data);

#endif

/*
**			printf("%f, %f, %f, %f, %f, %f, %d, %d.  %f, %f\n",
														values->min.real,
														values->min.im,
														values->max.real,
														values->max.im,
														values->factor.real,
														values->factor.im,
														values->max_iter,
														values->iter,
														values->center.im,
														values->center.real);
**
*/
