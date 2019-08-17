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

# include "fractol.h"

typedef struct		s_complex
{
	double			real;
	double			im;
}					t_complex;

typedef struct		s_mandelbrot
{
	int				max_iter;
	int				iter;
	t_complex		min;
	t_complex		max;
	t_complex		factor;
	t_complex		center;
	t_complex		z;
}					t_mandelbrot;

void				draw_mandelbrot_set(t_data *data);

#endif
