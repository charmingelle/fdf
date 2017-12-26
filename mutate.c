#include "header.h"

t_point get_modified_point(t_env *env, t_point *point)
{
	t_point p0;
	t_point p1;
	t_point rotated;

	p0.x = point->x * env->seglen;
	p0.y = (point->y * cos(degree_to_rad(env->angle_x)) + point->z
		* sin(degree_to_rad(env->angle_x))) * env->seglen;
	p0.z = (point->z * cos(degree_to_rad(env->angle_x)) - point->y
		* sin(degree_to_rad(env->angle_x))) * env->seglen;
	p1.x = p0.x * cos(degree_to_rad(env->angle_y)) - p0.z
		* sin(degree_to_rad(env->angle_y));
	p1.y = p0.y;
	p1.z = p0.z * cos(degree_to_rad(env->angle_y)) + p0.x
		* sin(degree_to_rad(env->angle_y));
	rotated.x = (p1.x * cos(degree_to_rad(env->angle_z)) + p1.y
		* sin(degree_to_rad(env->angle_z))) + (env->w_width / 2);
	rotated.y = (p1.y * cos(degree_to_rad(env->angle_z)) - p1.x
		* sin(degree_to_rad(env->angle_z))) + (env->w_height / 2);
	rotated.z = p1.z;
	rotated.color = point->color;
	return (rotated);
}
