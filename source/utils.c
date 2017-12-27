/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 14:11:15 by grevenko          #+#    #+#             */
/*   Updated: 2017/12/22 13:24:51 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

double				degree_to_rad(int degree)
{
	return (((double)degree * M_PI) / 180.0);
}

static unsigned int	hex_to_digit(char c)
{
	if (c >= 'a' && c <= 'f')
		return (c - 'a');
	if (c >= 'A' && c <= 'F')
		return (c - 'A');
	if (c >= '0' && c <= '9')
		return (c - '0');
	exit(show_invalid_color_error());
}

unsigned int		get_color(char *s)
{
	unsigned int	result;
	int				i;

	if ((ft_strlen(s) != 8) || (s[0] != '0') || (s[1] != 'x'))
		exit(show_invalid_color_error());
	result = 0;
	i = 2;
	while (i < 8)
		result = result * 16 + hex_to_digit(s[i++]);
	return (result);
}

void				sort(t_point *array)
{
	int		i;
	int		j;
	t_point	tmp;

	i = -1;
	while (++i < 3)
	{
		j = i - 1;
		while (++j < 3)
			if (array[j].y > array[i].y)
			{
				tmp = array[j];
				array[j] = array[i];
				array[i] = tmp;
			}
	}
}

void				clear_z_buffer(t_env *env)
{
	int	x;
	int	y;

	y = -1;
	while (++y < env->wheight && (x = -1))
		while (++x < env->wwidth)
			env->z_buff[y][x] = (t_z_buff_elem){0, 0};
}
