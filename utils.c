#include "header.h"

double	dist(t_point *a, t_point *b)
{
	return (sqrt(pow(a->x - b->x, 2) + pow(a->y - b->y, 2)));
}

void	ft_swap(double *a, double *b)
{
	double	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}
