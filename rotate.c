#include "header.h"

void	rotate_point_x(t_point **point, double angle)
{
	// (*point)->y = (*point)->y * cos(angle) + (*point)->z * sin(angle);
 //    (*point)->z = (*point)->z * cos(angle) - (*point)->y * sin(angle);
    (*point)->y = (*point)->y * cos(angle) - (*point)->z * sin(angle);
    (*point)->z = (*point)->y * sin(angle) + (*point)->z * cos(angle);
}

void	rotate_point_y(t_point **point, double angle)
{
	// (*point)->x = (*point)->x * cos(angle) - (*point)->z * sin(angle);
	// (*point)->z = (*point)->z * cos(angle) +  (*point)->x * sin(angle);
	(*point)->x = (*point)->x * cos(angle) + (*point)->z * sin(angle);
	(*point)->z = (-1) * (*point)->x * sin(angle) + (*point)->z * cos(angle);
}

void	rotate_point_z(t_point **point, double angle)
{
	// (*point)->x = (*point)->x * cos(angle) + (*point)->y * sin(angle);
	// (*point)->y = (*point)->y * cos(angle) - (*point)->x * sin(angle);
	(*point)->x = (*point)->x * cos(angle) - (*point)->y * sin(angle);
	(*point)->y = (*point)->x * sin(angle) + (*point)->y * cos(angle);
}

t_point	**get_rotated_point(t_env *env, t_point *point)
{
	t_point **new;

	new = (t_point **)malloc(sizeof(t_point *));
	*new = (t_point *)malloc(sizeof(t_point));
	(*new)->x = point->x;
	(*new)->y = point->y;
	(*new)->z = point->z;
	if (env->angle_x != 0)
		rotate_point_x(new, env->angle_x);
	if (env->angle_y != 0)
		rotate_point_y(new, env->angle_y);
	if (env->angle_z != 0)
		rotate_point_z(new, env->angle_z);
	return (new);
}
