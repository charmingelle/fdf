#include "header.h"

int				ft_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

void			ft_swap(t_point **a, t_point **b)
{
	t_point	*c;

	c = *a;
	*a = *b;
	*b = c;
}

t_point			**get_points_from_z_coords(char **z_coords, int row_number)
{
	t_point	**points;
	int		amount;
	int		i;
	
	amount = 0;
	while (z_coords[amount])
		amount++;
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

t_point_row		*create_point_set(int fd)
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
		add_point_row(&point_row, get_points_from_z_coords(z_coords, row_number));
		free_z_coords(z_coords);
		row_number++;
	}
	// printf("%p\n", point_row);
	// while (point_row)
	// {
	// 	printf("here\n");
	// 	print_point_row(point_row);
	// 	point_row = point_row->next;
	// }
	return (point_row);
}
