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

void	print_seg(t_seg *seg)
{
	printf("s(%g %g)-(%g %g) ", seg->a->x, seg->a->y, seg->b->x, seg->b->y);
}

void	print_segs(t_seg **segs)
{
	t_seg	*tmp;
	tmp = *segs;
	while ((tmp = tmp->next) != *segs)
	{
		print_seg(tmp);
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
