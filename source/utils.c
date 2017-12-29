/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/29 14:43:20 by grevenko          #+#    #+#             */
/*   Updated: 2017/12/29 14:46:51 by grevenko         ###   ########.fr       */
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
		return (c - 'a' + 10);
	if (c >= 'A' && c <= 'F')
		return (c - 'A' + 10);
	if (c >= '0' && c <= '9')
		return (c - '0');
	exit(show_invalid_color_error());
}

unsigned int		get_color(char *s)
{
	unsigned int	result;
	int				i;

	if ((s[0] != '0') || (s[1] != 'x'))
		exit(show_invalid_color_error());
	result = 0;
	i = 1;
	while (s[++i])
		result = result * 16 + hex_to_digit(s[i]);
	if (result > 0xFFFFFF)
		exit(show_invalid_color_error());
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
