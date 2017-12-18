#include "header.h"

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
		points[i] = get_point(row_number * SEG_LEN, i * SEG_LEN, ft_atoi(z_coords[i]) * SEG_LEN / 2);
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

t_point_row		*get_point_set(int fd, int *width, int *height)
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
