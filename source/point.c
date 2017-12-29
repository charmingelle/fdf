/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/29 14:43:20 by grevenko          #+#    #+#             */
/*   Updated: 2017/12/29 14:46:42 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_point		*get_point(double x, double y, double z, int color)
{
	t_point *point;

	if (!(point = (t_point *)malloc(sizeof(t_point))))
		exit(show_malloc_error());
	point->x = x;
	point->y = y;
	point->z = z;
	point->color = color;
	return (point);
}

void		move_point(t_point *point, double x_shift, double y_shift)
{
	point->x += x_shift;
	point->y += y_shift;
}

static int	equal_points(t_point *a, t_point *b)
{
	return ((a->x == b->x) && (a->y == b->y) && (a->z == b->z));
}

int			is_point_in_pointset(t_point *point, t_point **pointset)
{
	while (*pointset)
		if (equal_points(point, *pointset++))
			return (1);
	return (0);
}
