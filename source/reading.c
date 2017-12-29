/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/29 14:43:20 by grevenko          #+#    #+#             */
/*   Updated: 2017/12/29 14:46:48 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void		free_z_coords(char **z_coords)
{
	int	i;

	i = 0;
	while (z_coords[i])
		free(z_coords[i++]);
	free(z_coords);
}

static t_point	**get_points(t_env *env, char **z_coords, int y)
{
	static int	map_width;
	t_point		**pts;
	int			x;
	char		**temp;

	env->fwidth = 0;
	while (z_coords[env->fwidth])
		env->fwidth++;
	if (map_width == 0)
		(map_width = env->fwidth);
	else
		map_width != env->fwidth ? exit(show_invalid_size_error()) : 0;
	if (!(pts = (t_point **)malloc(sizeof(t_point *) * (env->fwidth + 1))))
		exit(show_malloc_error());
	x = -1;
	while (++x < env->fwidth)
	{
		temp = ft_strsplit(z_coords[x], ',');
		(temp[1] == 0) ?
		(pts[x] = get_point(x, y, ft_atoi(temp[0]), BASIC_COLOR)) :
		(pts[x] = get_point(x, y, ft_atoi(temp[0]), get_color(temp[1])));
		free_z_coords(temp);
	}
	pts[x] = NULL;
	return (pts);
}

void			set_figure(int fd, t_env *env)
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
		add_point_row(&point_row, get_points(env, z_coords, row_number));
		free_z_coords(z_coords);
		ft_memdel((void **)&row);
		row_number++;
	}
	env->fheight = row_number;
	env->pointset = point_row;
}
