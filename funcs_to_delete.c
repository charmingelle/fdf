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

void	print_plane(t_plane *plane)
{
	printf("plane->visibility = %g\n", plane->visibility);
}

void	print_all_planes(t_plane **plane)
{
	while (*plane)
	{
		print_plane(*plane);
		plane = &((*plane)->next);
	}
}
