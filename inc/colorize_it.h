/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colorize_it.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdudko <kdudko@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/08 18:18:56 by kdudko            #+#    #+#             */
/*   Updated: 2019/08/08 18:18:58 by kdudko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORIZE_IT_H
# define COLORIZE_IT_H

# define BLACK	0x000000
# define RED	0xFF0000
# define WHITE	0xFFFFFF

# define SET1 	0x6200A3
# define SET11 	0xEBCFFF
# define SET2 	0xFCA5F1
# define SET22 	0xB5FFFF
# define SET3 	0xD585FF
# define SET33 	0x00FFEE
# define SET4	0x13547A
# define SET44	0x80D0C7
# define SET5	0x283048
# define SET55	0x859398
# define SET6	0x3d7EAA
# define SET66	0xFFE47A
# define SET7	0x30CFD0
# define SET77	0x8a0000
# define SET8	0x5EE7DF
# define SET88	0xB490CA
# define SET9	0x0D324D
# define SET99	0x7F5A83
# define SET0	0x37D5D6
# define SET00	0x36096D

# define MENU	0x11FFF8

typedef struct		s_color
{
	int				r;
	int				g;
	int				b;
}					t_color;

#endif
