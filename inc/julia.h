/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdudko <kdudko@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 12:21:08 by kdudko            #+#    #+#             */
/*   Updated: 2019/09/07 12:21:12 by kdudko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JULIA_H
# define JULIA_H

# include "fractol.h"

typedef struct		s_set
{
	t_cnum			k;
	t_cnum			new_z;
	t_cnum			old_z;
}					t_set;


#endif
