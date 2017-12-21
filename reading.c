#include "header.h"

void	set_figure(int fd, t_env *env)
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
		add_point_row(&point_row, get_points_from_z_coords(env, z_coords, row_number));
		free_z_coords(z_coords);
		ft_memdel((void **)&row);
		row_number++;
	}
	env->f_height = row_number;
	env->pointset = point_row;
}

t_point		**get_points_from_z_coords(t_env *env, char **z_coords, int row_number)
{
	t_point	**points;
	int		i;
	
	env->f_width = 0;
	while (z_coords[env->f_width])
		env->f_width++;
	if (!(points = (t_point **)malloc(sizeof(t_point *) * (env->f_width + 1))))
		exit(1);
	i = 0;
	while (i < env->f_width)
	{
		points[i] = get_point(i, row_number, ft_atoi(z_coords[i]));
		i++;
	}
	points[i] = NULL;
	return (points);
}

void		free_z_coords(char **z_coords)
{
	int	i;

	i = 0;
	while (z_coords[i])
		free(z_coords[i++]);
	free(z_coords);
}
