#include "header.h"

t_point			**get_points_from_z_coords(char **z_coords, int line_number)
{
	t_point	**points;
	int		amount;
	int		i;
	
	amount = 0;
	while (z_coords[amount])
		amount++;
	if ((points = (t_point **)malloc(sizeof(t_point *) * (amount + 1))))
		exit(1);
	i = 0;
	while (i < amount)
	{
		points[i] = create_point(line_number, i, ft_atoi(z_coords[i]));
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

t_point_line	*create_point_set(int fd)
{
	char			*line;
	int				gnl_result;
	char			**z_coords;
	t_point_line	*point_line;
	int				line_number;

	point_line = NULL;
	line_number = 0;
	while ((gnl_result = get_next_line(fd, &line)))
	{
		if (!(z_coords = ft_strsplit(line, ' ')))
			exit(1);
		add_point_line(&point_line, get_points_from_z_coords(z_coords, line_number));
		free_z_coords(z_coords);
		line_number++;
	}
	return (point_line);
}
