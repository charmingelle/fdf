#include "header.h"

int		get_2d_x(t_env *env, t_point *point)
{
	// return (env->width / 2 + point->x);
	return (env->width / 2 + point->y - point->x * sin(DEGREE45));
	// return (env->width / 2 + point->x - point->z);
	// return (env->width / 2 + point->x - point->z * sin(DEGREE45));
}

int		get_2d_y(t_env *env, t_point *point)
{
	// return (env->height / 2 - point->y);
	return (env->height / 2 - point->z + point->x * cos(DEGREE45));
	// return (env->height / 2 + point->y + point->z);
	// return (env->height / 2 + point->y + point->z * cos(DEGREE45));
}

void	draw_point(t_env *env, t_point *point, int color)
{
	int x_2d;
	int y_2d;

	x_2d = get_2d_x(env, point);
	y_2d = get_2d_y(env, point);
	mlx_pixel_put(env->mlx, env->window, x_2d, y_2d, color);
}

void	draw_axis(t_env *env, int color)
{
	for (int x = (env->width - env->height) / 2; x < env->width - (env->width - env->height) / 2; x++)
		mlx_pixel_put(env->mlx, env->window, x, (-1) * x + (env->width + env->height) / 2, color);
	for (int x = 0; x < env->width; x++)
		mlx_pixel_put(env->mlx, env->window, x, env->height / 2, color);
	for (int y = 0; y < env->height; y++)
		mlx_pixel_put(env->mlx, env->window, env->width / 2, y, color);
}

void	draw_point_set(t_env *env)
{
	t_point	**points;
	int		i;

	while (env->point_set)
	{
		points = env->point_set->points;
		i = 0;
		while (points[i])
		{
			draw_point(env, points[i], env->color);
			i++;
		}
		env->point_set = env->point_set->next;
	}
}

void	erase_point_set(t_env *env)
{
	t_point	**points;
	int		i;

	while (env->point_set)
	{
		points = env->point_set->points;
		i = 0;
		while (points[i])
		{
			draw_point(env, points[i], 0x000000);
			i++;
		}
		env->point_set = env->point_set->next;
	}
}

void	draw_rotated(t_env *env, void(*f)(t_point **, int), int direction)
{
	// erase_point_set(env);
	mlx_clear_window(env->mlx, env->window);
	rotate_point_set(env, f, direction);
	draw_point_set(env);
}

int		square_function(int x)
{
	return (x * x);
}

void	draw_graph(t_env *env, int(*f)(int), int start, int end, int color)
{
	t_point *point;

	for (int x = start; x <= end; x++)
	{
		point = create_point(x, f(x) / 12, 0);
		draw_point(env, point, color);
		free(point);
	}
}

void	draw_segment(t_env *env, t_point *p1, t_point *p2, int color)
{
	int a_x_2d;
	int a_y_2d;
	int b_x_2d;
	int b_y_2d;
	int a;
	int b;

	a_x_2d = get_2d_x(env, p1);
	a_y_2d = get_2d_y(env, p1);
	b_x_2d = get_2d_x(env, p2);
	b_y_2d = get_2d_y(env, p2);

	a = (b_y_2d - a_y_2d) / (b_x_2d - a_x_2d);
	b = a_y_2d - b_y_2d;
	for (int x = a_x_2d; x < a_y_2d; x++)
		mlx_pixel_put(env->mlx, env->window, x, a * x + b, color);
}
