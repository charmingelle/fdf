#include "header.h"

// void	rotate_point_x(t_point **point, double angle)
// {
// 	// (*point)->y = (*point)->y * cos(angle) + (*point)->z * sin(angle);
//  //    (*point)->z = (*point)->z * cos(angle) - (*point)->y * sin(angle);
//     (*point)->y = (*point)->y * cos(angle) - (*point)->z * sin(angle);
//     (*point)->z = (*point)->y * sin(angle) + (*point)->z * cos(angle);
// }

// void	rotate_point_y(t_point **point, double angle)
// {
// 	// (*point)->x = (*point)->x * cos(angle) - (*point)->z * sin(angle);
// 	// (*point)->z = (*point)->z * cos(angle) +  (*point)->x * sin(angle);
// 	(*point)->x = (*point)->x * cos(angle) + (*point)->z * sin(angle);
// 	(*point)->z = (-1) * (*point)->x * sin(angle) + (*point)->z * cos(angle);
// }

// void	rotate_point_z(t_point **point, double angle)
// {
// 	// (*point)->x = (*point)->x * cos(angle) + (*point)->y * sin(angle);
// 	// (*point)->y = (*point)->y * cos(angle) - (*point)->x * sin(angle);
// 	(*point)->x = (*point)->x * cos(angle) - (*point)->y * sin(angle);
// 	(*point)->y = (*point)->x * sin(angle) + (*point)->y * cos(angle);
// }

t_point	**get_rotated_point(t_env *env, t_point *point)
{
	t_point	p0;
	t_point	p1;
	t_point	**p2;

	p2 = (t_point **)malloc(sizeof(t_point *));
	*p2 = (t_point *)malloc(sizeof(t_point));
	p0.x = point->x;
	p0.y = point->y * cos(env->angle_x) + point->z * sin(env->angle_x);
	p0.z = point->z * cos(env->angle_x) - point->y * sin(env->angle_x);
	p1.x = p0.x * cos(env->angle_y) - p0.z * sin(env->angle_y);
	p1.y = p0.y;
	p1.z = p0.z * cos(env->angle_y) + p0.x * sin(env->angle_y);
	(*p2)->x = p1.x * cos(env->angle_z) + p1.y * sin(env->angle_z);
	(*p2)->y = p1.y * cos(env->angle_z) - p1.x * sin(env->angle_z);
	(*p2)->z = p1.z;
	return (p2);
}


/*
#include "header.h"

t_point	rotate_point_x(t_point *point, double angle)
{
	t_point tmp;

	tmp.y = point->y * cos(angle) + point->z * sin(angle);
    tmp.z = point->z * cos(angle) - point->y * sin(angle);
    // (*point)->y = (*point)->y * cos(angle) - (*point)->z * sin(angle);
    // (*point)->z = (*point)->y * sin(angle) + (*point)->z * cos(angle);
    return (tmp);
}

t_point	rotate_point_y(t_point *point, double angle)
{
	t_point tmp;

	tmp.x = point->x * cos(angle) - point->z * sin(angle);
	tmp.z = point->z * cos(angle) +  point->x * sin(angle);
	// (*point)->x = (*point)->x * cos(angle) + (*point)->z * sin(angle);
	// (*point)->z = (-1) * (*point)->x * sin(angle) + (*point)->z * cos(angle);
	return (tmp);
}

t_point	rotate_point_z(t_point *point, double angle)
{
	t_point tmp;

	tmp.x = point->x * cos(angle) + point->y * sin(angle);
	tmp.y = point->y * cos(angle) - point->x * sin(angle);
	// (*point)->x = (*point)->x * cos(angle) - (*point)->y * sin(angle);
	// (*point)->y = (*point)->x * sin(angle) + (*point)->y * cos(angle);
	return (tmp);
}

t_point	**get_rotated_point(t_env *env, t_point *point)
{
	t_point	p0;
	t_point	p1;
	t_point	tmp;
	t_point	**p2;

	p2 = (t_point **)malloc(sizeof(t_point *));
	*p2 = (t_point *)malloc(sizeof(t_point));
	p0 = rotate_point_x(point, env->angle_x);
	p1 = rotate_point_y(&p0, env->angle_y);
	tmp = rotate_point_z(&p1, env->angle_z);
	(*p2)->x = tmp.x;
	(*p2)->y = tmp.y;
	(*p2)->z = p1.z;
	return (p2);
}*/