#include "header.h"

void	rotate_point_x(t_point **point, int direction)
{
	double	angle;

	if (direction == 1)
		angle = DEGREE5;
	else
		angle = (-1) * DEGREE5;
    (*point)->y = (int)((*point)->y * cos(angle) - (*point)->z * sin(angle));
    (*point)->z = (int)((*point)->y * sin(angle) + (*point)->z * cos(angle));
}

void	rotate_point_y(t_point **point, int direction)
{
	double	angle;

	if (direction == 1)
		angle = DEGREE5;
	else
		angle = (-1) * DEGREE5;
	(*point)->x = (int)((*point)->x * cos(angle) + (*point)->z * sin(angle));
	(*point)->z = (int)((-1) * (*point)->x * sin(angle) + (*point)->z * cos(angle));
}

void	rotate_point_z(t_point **point, int direction)
{
	double	angle;

	if (direction == 1)
		angle = DEGREE5;
	else
		angle = (-1) * DEGREE5;
	(*point)->x = (int)((*point)->x * cos(angle) - (*point)->y * sin(angle));
	(*point)->y = (int)((*point)->x * sin(angle) + (*point)->y * cos(angle));
}

void	rotate_point_set(t_env *env, void(*f)(t_point **, int), int direction)
{
	t_point		**points;
	t_point_row	*temp;
	int			i;

	temp = env->point_set;
	while (temp)
	{
		i = 0;
		while (temp->points[i])
		{
			f(&(temp->points[i]), direction);
			i++;
		}
		temp = temp->next;
	}
}
