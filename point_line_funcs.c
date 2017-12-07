#include "header.h"

t_point_line	*create_point_line(t_point **points)
{
	t_point_line *point_line;

	if (!(point_line = (t_point_line *)malloc(sizeof(t_point_line))))
		exit(1);
	point_line->prev = NULL;
	point_line->points = points;
	point_line->next = NULL;
	return (point_line);
}

void			add_point_line(t_point_line **point_line, t_point **points)
{
	t_point_line *new;

	new = create_point_line(points);
	if (*point_line == NULL)
		*point_line = new;
	else
	{
		while ((*point_line)->next)
			point_line = &((*point_line)->next);
		(*point_line)->next = new;
		new->prev = (*point_line);
	}
}
