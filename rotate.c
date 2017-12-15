#include "header.h"

// t_point	**get_rotated_point(t_env *env, t_point *point)
// {
// 	t_point	p0;
// 	t_point	p1;
// 	t_point	**p2;

// 	p2 = (t_point **)malloc(sizeof(t_point *));
// 	*p2 = (t_point *)malloc(sizeof(t_point));
// 	p0.x = point->x;
// 	p0.y = point->y * cos(env->angle_x) + point->z * sin(env->angle_x);
// 	p0.z = point->z * cos(env->angle_x) - point->y * sin(env->angle_x);
// 	p1.x = p0.x * cos(env->angle_y) - p0.z * sin(env->angle_y);
// 	p1.y = p0.y;
// 	p1.z = p0.z * cos(env->angle_y) + p0.x * sin(env->angle_y);
// 	(*p2)->x = p1.x * cos(env->angle_z) + p1.y * sin(env->angle_z);
// 	(*p2)->y = p1.y * cos(env->angle_z) - p1.x * sin(env->angle_z);
// 	(*p2)->z = p1.z;
// 	return (p2);
// }

t_point *get_rotated_point(t_env *env, t_point *point)
{
    t_point p0;
    t_point p1;
    t_point *rotated;

    rotated = (t_point *)malloc(sizeof(t_point));
    p0.x = point->x;
    p0.y = point->y * cos(env->angle_x) + point->z * sin(env->angle_x);
    p0.z = point->z * cos(env->angle_x) - point->y * sin(env->angle_x);
    p1.x = p0.x * cos(env->angle_y) - p0.z * sin(env->angle_y);
    p1.y = p0.y;
    p1.z = p0.z * cos(env->angle_y) + p0.x * sin(env->angle_y);
    rotated->x = p1.x * cos(env->angle_z) + p1.y * sin(env->angle_z);
    rotated->y = p1.y * cos(env->angle_z) - p1.x * sin(env->angle_z);
    rotated->z = p1.z;
    return (rotated);
}
