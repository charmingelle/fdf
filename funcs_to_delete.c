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

void	print_segment(t_segment *segment)
{
	printf("s(%g %g)-(%g %g) ", segment->a->x, segment->a->y, segment->b->x, segment->b->y);
}

void	print_segments(t_segment **segments)
{
	t_segment	*tmp;
	tmp = *segments;
	while ((tmp = tmp->next) != *segments)
	{
		print_segment(tmp);
		printf("\n");
	}
}

void	print_flat(t_flat *flat)
{
	printf("f(%g %g)-(%g %g)-(%g %g)-(%g %g) ",
			flat->a->x, flat->a->y,
			flat->b->x, flat->b->y,
			flat->c->x, flat->c->y,
			flat->d->x, flat->d->y);
}

void	print_flats(t_flat **flats)
{
	while (*flats)
	{
		print_flat(*flats);
		flats = &((*flats)->next);
		printf("\n");
	}
}
