/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdudko <kdudko@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 20:14:38 by kdudko            #+#    #+#             */
/*   Updated: 2019/08/13 20:14:40 by kdudko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../inc/fractol.h"

void	error(char *message)
{
	perror(message);
	exit(EXIT_FAILURE);
}

void	invalid_param(void)
{
	ft_putendl("usage: ./fractol param");
	ft_putendl("\navailable params:");
	ft_putendl("Julia");
	ft_putendl("Mandelbrot");
	exit(EXIT_FAILURE);
}

int		assign_num(t_data *data)
{
	if ((ft_strncmp("Julia", data->name, ft_strlen("Julia"))) == 0)
		return (1);
	if ((ft_strncmp("Mandelbrot", data->name, ft_strlen("Mandelbrot"))) == 0)
		return (2);
	return (0);
}

void	get_fractal_type(const char *input, t_data *data)
{
	size_t	s_len;

	s_len = ft_strlen(input);
	data->name = ft_strndup(input, s_len);
	data->type = assign_num(data);
	if (data->type == 0)
		invalid_param();
}
