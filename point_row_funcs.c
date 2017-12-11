#include "header.h"

t_point_row	*create_point_row(t_point **points)
{
	t_point_row *point_row;

	if (!(point_row = (t_point_row *)malloc(sizeof(t_point_row))))
		exit(1);
	point_row->points = points;
	point_row->next = NULL;
	return (point_row);
}

void		add_point_row(t_point_row **point_row, t_point **points)
{
	t_point_row *new;

	new = create_point_row(points);
	if (*point_row == NULL)
		*point_row = new;
	else
	{
		new->next = *point_row;
		*point_row = new;
	}
}
