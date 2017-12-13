#include "header.h"

void			ft_swap(t_point **a, t_point **b)
{
	t_point	*c;

	c = *a;
	*a = *b;
	*b = c;
}

t_point			**get_points_from_z_coords(char **z_coords, int row_number, int *width)
{
	t_point	**points;
	int		amount;
	int		i;
	
	amount = 0;
	while (z_coords[amount])
		amount++;
	*width = amount;
	if (!(points = (t_point **)malloc(sizeof(t_point *) * (amount + 1))))
		exit(1);
	i = 0;
	while (i < amount)
	{
		points[i] = create_point(row_number * SEGMENT_LEN, i * SEGMENT_LEN, ft_atoi(z_coords[i]) * SEGMENT_LEN / 2);
		i++;
	}
	points[i] = NULL;
	return (points);
}

void			free_z_coords(char **z_coords)
{
	int	i;

	i = 0;
	while (z_coords[i])
		free(z_coords[i++]);
	free(z_coords);
}

t_point_row		*create_point_set(int fd, int *width, int *height)
{
	char			*row;
	int				gnl_result;
	char			**z_coords;
	int				row_number;
	t_point_row		*point_row;

	row_number = 0;
	point_row = NULL;
	while ((gnl_result = get_next_line(fd, &row)) > 0)
	{
		if (!(z_coords = ft_strsplit(row, ' ')))
			exit(1);
		add_point_row(&point_row, get_points_from_z_coords(z_coords, row_number, width));
		free_z_coords(z_coords);
		row_number++;
	}
	*height = row_number;
	return (point_row);
}

t_point			*get_flat_segment_cross(t_segment *s1, t_segment *s2)
{
	double	x1;
	double	x2;
	double	x3;
	double	x4;
	double	y1;
	double	y2;
	double	y3;
	double	y4;
	double	a1;
	double	b1;
	double	c1;
	double	a2;
	double	b2;
	double	c2;
	double	x;
	double	y;

	x1 = s1->a->x;
	x2 = s1->b->x;
	x3 = s2->a->x;
	x4 = s2->b->x;
	y1 = s1->a->y;
	y2 = s1->b->y;
	y3 = s2->a->y;
	y4 = s2->b->y;
	a1 = y2 - y1;
	b1 = x1 - x2;
	c1 = x2 * y1 - y2 * x1;
	a2 = y4 - y3;
	b2 = x3 - x4;
	c2 = x4 * y3 - y4 * x3;
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
	if ( ((x >= x1 && x <= x2) || (x >= x2 && x <= x1)) && ((y >= y1 && y <= y2) || (y >= y2 && y <= y1))
		&& ((x >= x3 && x <= x4) || (x >= x4 && x <= x3)) && ((y >= y3 && y <= y4) || (y >= y4 && y <= y3)))
		return (create_point(x, y, 0));
	return (NULL);
}
