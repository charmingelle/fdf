#include "header.h"

void	ft_swap(void **a, void **b)
{
	void *temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

double	degree_to_rad(int degree)
{
	return (((double)degree * M_PI) / 180.0);
}
