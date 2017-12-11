#include "header.h"

double	get_2d_x(t_env *env, t_point *point)
{
	return (env->width / 2 + point->y - point->x * sin(DEGREE45));
	// return (env->width / 2 + point->y - point->x * sin(DEGREE45));
	// return (env->width / 2 + point->y);
	// return (env->width / 2 + point->y - point->x);
	// return (point->y - point->x * sin(DEGREE45));
	// return (env->width / 2 + point->x);
	// return (env->width / 2 + point->x - point->z);
	// return (env->width / 2 + point->x - point->z * sin(DEGREE45));
}

double	get_2d_y(t_env *env, t_point *point)
{
	return (env->height / 2 - point->z + point->x * cos(DEGREE45));
	// return (env->height / 2 - point->z + point->x * cos(DEGREE45));
	// return (env->height / 2 - point->z);
	// return (env->height / 2 - point->z + point->x);
	// return ((-1) * point->z + point->x * cos(DEGREE45));
	// return (env->height / 2 - point->y);
	// return (env->height / 2 + point->y + point->z);
	// return (env->height / 2 + point->y + point->z * cos(DEGREE45));
}

void	draw_axis(t_env *env, int color)
{
	for (double x = (env->width - env->height) / 2; x < env->width - (env->width - env->height) / 2; x++)
		mlx_pixel_put(env->mlx, env->window, x, (-1) * x + (env->width + env->height) / 2, color);
	for (double x = 0; x < env->width; x++)
		mlx_pixel_put(env->mlx, env->window, x, env->height / 2, color);
	for (double y = 0; y < env->height; y++)
		mlx_pixel_put(env->mlx, env->window, env->width / 2, y, color);
}

void	draw(t_env *env)
{
	t_point		**points;
	t_point_row	*temp;
	int			i;

	temp = env->point_set;
	while (temp->next)
	{
		draw_segment(env, get_rotated_point(env, temp->next->points[0]), get_rotated_point(env, temp->points[0]));
		i = 1;
		while (temp->points[i])
		{
			draw_segment(env, get_rotated_point(env, temp->points[i - 1]), get_rotated_point(env, temp->points[i]));
			draw_segment(env, get_rotated_point(env, temp->next->points[i]), get_rotated_point(env, temp->points[i]));
			i++;
		}
		temp = temp->next;
	}
	i = 1;
	while (temp->points[i])
	{
		draw_segment(env, get_rotated_point(env, temp->points[i - 1]), get_rotated_point(env, temp->points[i]));
		i++;
	}
}

void	draw_segment(t_env *env, t_point **p1, t_point **p2)
{
	double 	x1;
	double 	y1;
	double 	x2;
	double 	y2;
	double	t;
	int		color;

	if ((*p1)->z > (*p2)->z)
		ft_swap(p1, p2);
	// x1 = (*p1)->x + env->width / 2;
	// y1 = -(*p1)->y + env->height / 2;
	// x2 = (*p2)->x + env->width / 2;
	// y2 = -(*p2)->y + env->height / 2;
	x1 = get_2d_x(env, *p1);
	y1 = get_2d_y(env, *p1);
	x2 = get_2d_x(env, *p2);
	y2 = get_2d_y(env, *p2);
	color = env->color;
	t = -1.00;
	while (t <= 0)
	{
		mlx_pixel_put(env->mlx, env->window, (x1 - x2) * t + x1, (y1 - y2) * t + y1, color);
		if (color + 1 <= 0xFFFFFF)
			color += 1;
		t += 0.001;
	}
	free(*p1);
	free(*p2);
}
