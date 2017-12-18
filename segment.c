#include "header.h"

t_seg	*get_seg(t_point *a, t_point *b)
{
	t_seg *seg;

	seg = (t_seg *)malloc(sizeof(t_seg));
	seg->a = a;
	seg->b = b;
	seg->next = seg;
	seg->prev = seg;
	return (seg);
}

void    add_seg(t_seg **segs, t_seg *new)
{
	(*segs)->next->prev = new;
	new->next = (*segs)->next;
	new->prev = *segs;
	(*segs)->next = new;
}

void	add_seg_back(t_seg **segs, t_seg *new)
{
	new->prev = (*segs)->prev;
	new->next = *segs;
	(*segs)->prev->next = new;
	(*segs)->prev = new;
}

void	delete_seg(t_seg *to_delete)
{
	to_delete->next->prev = to_delete->prev;
	to_delete->prev->next = to_delete->next;
	ft_memdel((void **)&to_delete->a);
	ft_memdel((void **)&to_delete->b);
	ft_memdel((void **)&to_delete);
}

double	get_z_index(t_point *start, t_point *end, double x, double y)
{
	double	t;

	if ((start->x - end->x) != 0)
		t = (x - start->x) / (start->x - end->x);
	else
		t = (y - start->y) / (start->y - end->y);
	return ((start->z - end->z) * t + start->z);
}

t_point	*get_segs_cross(t_point *a_start, t_point *a_end, t_point *b_start, t_point *b_end)
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
		// if (a1 != 0 && b1 != 0 && a2 == 0 && b2 != 0)
		y = -c2 / b2;
		x = (-b1 * y - c1) / a1;
	}
	if ( ((x >= a_start->x && x <= a_end->x) || (x >= a_end->x && x <= a_start->x)) && ((y >= a_start->y && y <= a_end->y) || (y >= a_end->y && y <= a_start->y))
		&& ((x >= b_start->x && x <= b_end->x) || (x >= b_end->x && x <= b_start->x)) && ((y >= b_start->y && y <= b_end->y) || (y >= b_end->y && y <= b_start->y)))
		return (get_point(x, y, get_z_index(a_start, a_end, x, y)));
	return (NULL);
}

t_point	**get_seg_flat_cross(t_seg *seg, t_flat *flat)
{
	t_point **cross;
	t_point	*temp;
	int		i;

	if (!(cross = ft_memalloc(sizeof(t_point *) * 5)))
		exit(1);
	i = 0;
	if ((temp = get_segs_cross(seg->a, seg->b, flat->a, flat->b)) && !is_point_in_pointset(temp, cross))
		cross[i++] = temp;
	if ((temp = get_segs_cross(seg->a, seg->b, flat->b, flat->c)) && !is_point_in_pointset(temp, cross))
		cross[i++] = temp;
	if ((temp = get_segs_cross(seg->a, seg->b, flat->c, flat->d)) && !is_point_in_pointset(temp, cross))
		cross[i++] = temp;
	if ((temp = get_segs_cross(seg->a, seg->b, flat->d, flat->a)) && !is_point_in_pointset(temp, cross))
		cross[i++] = temp;
	return (cross);
}
