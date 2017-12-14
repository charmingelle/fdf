#include "header.h"

void	print_point(t_point *point)
{
	printf("(%g, %g, %g)\n", point->x, point->y, point->z);
}

void	print_point_row(t_point_row *point_row)
{
	int i;

	i = 0;
	while ((point_row->points)[i] != NULL)
	{
		print_point((point_row->points)[i]);
		i++;
	}
	printf("\n");
}
