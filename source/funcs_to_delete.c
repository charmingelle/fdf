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

void	print_point(t_point *point)
{
	printf("(%g, %g, %g)\n", point->x, point->y, point->z);
}

void	print_point_row(t_point_row *point_row)
{
	int i;

	i = 0;
	while ((point_row->points)[i] != NULL)
	{
		print_point((point_row->points)[i]);
		i++;
	}
	printf("\n");
}

void	draw_axis(t_env *env, int color)
{
	for (double x = (env->wwidth - env->wheight) / 2; x < env->wwidth - (env->wwidth - env->wheight) / 2; x++)
		mlx_pixel_put(env->mlx, env->window, x, (-1) * x + (env->wwidth + env->wheight) / 2, color);
	for (double x = 0; x < env->wwidth; x++)
		mlx_pixel_put(env->mlx, env->window, x, env->wheight / 2, color);
	for (double y = 0; y < env->wheight; y++)
		mlx_pixel_put(env->mlx, env->window, env->wwidth / 2, y, color);
}

void	print_cross(t_point **points)
{
	int i;

	i = -1;
	while (points[++i])
		print_point(points[i]);
}
