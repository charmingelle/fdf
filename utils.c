#include "header.h"

void	ft_swap(t_point **a, t_point **b)
{
	t_point	*c;

	c = *a;
	*a = *b;
	*b = c;
}
