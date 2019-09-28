/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_points.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdudko <kdudko@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 23:22:29 by kdudko            #+#    #+#             */
/*   Updated: 2019/09/27 23:22:30 by kdudko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

double	iter_to_double(t_cnum n, int iter)
{
	double log_1;
	double log_2;
	double div;

	log_1 = log(hypot(n.re, n.im));
	log_2 = log(log_1);
	div = log_2 / log(2);
	return (iter + 1.0 - div);
}

void	count_points(t_data *data, t_set *set)
{
	double temp;

	set->iter = 0;
	set_complex(&(set->z_sqrt),
		set->new_z.re * set->new_z.re, set->new_z.im * set->new_z.im);
	while (set->iter < data->params->max_iter)
	{
		if (data->type == burning_ship)
			set_complex(&(set->old_z), fabs(set->new_z.re),
										fabs(set->new_z.im) * -1.0);
		else
			set_complex(&(set->old_z), set->new_z.re, set->new_z.im);
		temp = set->z_sqrt.re - set->z_sqrt.im;
		set->new_z.re = temp + set->c.re;
		temp = set->old_z.re + set->old_z.re;
		temp = (data->type == tricorn) ? -temp : temp;
		set->new_z.im = temp * set->old_z.im + set->c.im;
		set_complex(&(set->z_sqrt),
			set->new_z.re * set->new_z.re, set->new_z.im * set->new_z.im);
		temp = set->z_sqrt.re + set->z_sqrt.im;
		set->iter++;
		if (temp > 4)
			break ;
	}
	set->iter_double = iter_to_double(set->new_z, set->iter);
}

void	count_menu_points(t_data *data, t_set *set, int i)
{
	double temp;

	set->iter = 0;
	set_complex(&(set->z_sqrt),
		set->new_z.re * set->new_z.re, set->new_z.im * set->new_z.im);
	while (set->iter < data->params->max_iter)
	{
		if (data->small_img[i].type == burning_ship)
			set_complex(&(set->old_z), fabs(set->new_z.re),
										fabs(set->new_z.im) * -1.0);
		else
			set_complex(&(set->old_z), set->new_z.re, set->new_z.im);
		temp = set->z_sqrt.re - set->z_sqrt.im;
		set->new_z.re = temp + set->c.re;
		temp = set->old_z.re + set->old_z.re;
		temp = (data->small_img[i].type == tricorn) ? -temp : temp;
		set->new_z.im = temp * set->old_z.im + set->c.im;
		set_complex(&(set->z_sqrt),
			set->new_z.re * set->new_z.re, set->new_z.im * set->new_z.im);
		temp = set->z_sqrt.re + set->z_sqrt.im;
		set->iter++;
		if (temp > 4)
			break ;
	}
	set->iter_double = iter_to_double(set->new_z, set->iter);
}
