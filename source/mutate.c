/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/29 14:43:20 by grevenko          #+#    #+#             */
/*   Updated: 2017/12/29 14:46:39 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_point	get_modified_point(t_env *env, t_point *point)
{
	t_point p0;
	t_point p1;
	t_point rotated;

	p0.x = point->x * env->seglen;
	p0.y = (point->y * cos(degree_to_rad(env->ang_x)) + point->z
		* sin(degree_to_rad(env->ang_x))) * env->seglen;
	p0.z = (point->z * cos(degree_to_rad(env->ang_x)) - point->y
		* sin(degree_to_rad(env->ang_x))) * env->seglen;
	p1.x = p0.x * cos(degree_to_rad(env->ang_y)) - p0.z
		* sin(degree_to_rad(env->ang_y));
	p1.y = p0.y;
	p1.z = p0.z * cos(degree_to_rad(env->ang_y)) + p0.x
		* sin(degree_to_rad(env->ang_y));
	rotated.x = (p1.x * cos(degree_to_rad(env->ang_z)) + p1.y
		* sin(degree_to_rad(env->ang_z))) + env->shift_x;
	rotated.y = (p1.y * cos(degree_to_rad(env->ang_z)) - p1.x
		* sin(degree_to_rad(env->ang_z))) + env->shift_y;
	rotated.z = p1.z;
	rotated.color = point->color;
	return (rotated);
}
