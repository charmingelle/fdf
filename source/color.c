/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/29 14:54:15 by grevenko          #+#    #+#             */
/*   Updated: 2017/12/29 15:02:31 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	get_r(int color)
{
	return (color / 0x10000);
}

static int	get_g(int color)
{
	return ((color - (color / 0x10000) * 0x10000) / 0x100);
}

static int	get_b(int color)
{
	return (color % 0x100);
}

int			get_mid_color(int start, int end, double to_pass, double passed)
{
	int		r;
	int		g;
	int		b;
	double	rgb_steps[3];

	rgb_steps[0] = (get_r(end) - get_r(start)) / to_pass;
	rgb_steps[1] = (get_g(end) - get_g(start)) / to_pass;
	rgb_steps[2] = (get_b(end) - get_b(start)) / to_pass;
	r = get_r(start) + (rgb_steps[0] * passed);
	g = get_g(start) + (rgb_steps[1] * passed);
	b = get_b(start) + (rgb_steps[2] * passed);
	return (r * 0x10000 + g * 0x100 + b);
}
