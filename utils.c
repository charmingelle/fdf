#include "header.h"

void	double_swap(double *a, double *b)
{
	double	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	point_swap(t_point *a, t_point *b)
{
	t_point	*temp;

	temp = a;
	a = b;
	b = temp;
}
