#include "header.h"

void	ft_swap(void **a, void **b)
{
	void *temp;

	temp = *a;
	*a = *b;
	*b = temp;
}
