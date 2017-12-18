#include "header.h"

t_point *get_point(double x, double y, double z)
{
	t_point *point;

	point = (t_point *)malloc(sizeof(t_point));
	point->x = x;
	point->y = y;
	point->z = z;
	return (point);
}

int		equal_points(t_point *a, t_point *b)
{
	return ((a->x == b->x) && (a->y == b->y) && (a->z == b->z));
}

int		is_point_in_pointset(t_point *point, t_point **pointset)
{
	while (*pointset)
		if (equal_points(point, *pointset++))
			return (1);
	return (0);
}
