#include "header.h"

t_segment	*create_segment(t_point *a, t_point *b)
{
	t_segment *segment;

	segment = (t_segment *)malloc(sizeof(t_segment));
	segment->a = a;
	segment->b = b;
	segment->next = NULL;
	return (segment);
}

t_point			*get_segments_cross(t_point *a_start, t_point *a_end, t_point *b_start, t_point *b_end)
{
	double	a1;
	double	b1;
	double	c1;
	double	a2;
	double	b2;
	double	c2;
	double	x;
	double	y;

	a1 = a_end->y - a_start->y;
	b1 = a_start->x - a_end->x;
	c1 = a_end->x * a_start->y - a_end->y * a_start->x;
	a2 = b_end->y - b_start->y;
	b2 = b_start->x - b_end->x;
	c2 = b_end->x * b_start->y - b_end->y * b_start->x;
	if (a1 != 0 && b1 != 0 && a2 != 0 && b2 != 0)
	{
		y = (a2 * c1 / a1 - c2) / (b2 - (a2 * b1 / a1));
		x = (-b1 * y - c1) / a1; 
	}
	else if (a1 != 0 && b1 == 0 && a2 != 0 && b2 != 0)
	{
		x = -c1 / a1;
		y = (-a2 * x - c2) / b2;
	}
	else if (a1 != 0 && b1 == 0 && a2 != 0 && b2 == 0)
		return (NULL);
	else if (a1 != 0 && b1 == 0 && a2 == 0 && b2 != 0)
	{
		x = -c1 / a1;
		y = -c2 / b2;
	}
	else if (a1 == 0 && b1 != 0 && a2 != 0 && b2 != 0)
	{
		y = -c1 / b1;
		x = (-b2 * y - c2) / a2;
	}
	else if (a1 == 0 && b1 != 0 && a2 != 0 && b2 == 0)
	{
		y = -c1 / b1;
		x = -c2 / a2;
	}
	else if (a1 == 0 && b1 != 0 && a2 == 0 && b2 != 0)
		return (NULL);
	else if (a1 != 0 && b1 != 0 && a2 != 0 && b2 == 0)
	{
		x = -c2 / a2;
		y = (-a1 * x - c1) / b1;
	}
	else
	{
		// if (a1 != 0 && b1 != 0 && a2 == 0 && b2 != 0)ß
		y = -c2 / b2;
		x = (-b1 * y - c1) / a1;
	}
	if ( ((x >= a_start->x && x <= a_end->x) || (x >= a_end->x && x <= a_start->x)) && ((y >= a_start->y && y <= a_end->y) || (y >= a_end->y && y <= a_start->y))
		&& ((x >= b_start->x && x <= b_end->x) || (x >= b_end->x && x <= b_start->x)) && ((y >= b_start->y && y <= b_end->y) || (y >= b_end->y && y <= b_start->y)))
		return (create_point(x, y, 0));
	return (NULL);
}

t_point	**get_segment_flat_cross(t_segment *segment, t_flat *flat)
{
	t_point **cross;
	t_point	*temp;
	int		i;

	if (!(cross = ft_memalloc(sizeof(t_point *) * 5)))
		exit(1);
	i = 0;
	if ((temp = get_segments_cross(segment->a, segment->b, flat->a, flat->b)) && !is_point_in_pointset(temp, cross))
		cross[i++] = temp;
	if ((temp = get_segments_cross(segment->a, segment->b, flat->b, flat->c)) && !is_point_in_pointset(temp, cross))
		cross[i++] = temp;
	if ((temp = get_segments_cross(segment->a, segment->b, flat->c, flat->d)) && !is_point_in_pointset(temp, cross))
		cross[i++] = temp;
	if ((temp = get_segments_cross(segment->a, segment->b, flat->d, flat->a)) && !is_point_in_pointset(temp, cross))
		cross[i++] = temp;
	return (cross);
}
