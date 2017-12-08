#include "header.h"

int		get_2d_x(t_env *env, t_point *point)
{
	// return (point->y - point->x * sin(DEGREE45));
	return (env->width / 2 + point->y - point->x * sin(DEGREE45));
	// return (env->width / 2 + point->x);
	// return (env->width / 2 + point->x - point->z);
	// return (env->width / 2 + point->x - point->z * sin(DEGREE45));
}

int		get_2d_y(t_env *env, t_point *point)
{
	// return ((-1) * point->z + point->x * cos(DEGREE45));
	return (env->height / 2 - point->z + point->x * cos(DEGREE45));
	// return (env->height / 2 - point->y);
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
	t_point		**points;
	t_point_row	*temp;
	int			i;

	temp = env->point_set;
	while (temp->next)
	{
		draw_segment(env, temp->next->points[0], temp->points[0]);
		i = 1;
		while (temp->points[i])
		{
			draw_segment(env, temp->points[i - 1], temp->points[i]);
			draw_segment(env, temp->next->points[i], temp->points[i]);
			i++;
		}
		temp = temp->next;
	}
	i = 1;
	while (temp->points[i])
	{
		draw_segment(env, temp->points[i - 1], temp->points[i]);
		i++;
	}
}

// void	draw_point_set(t_env *env)
// {
// 	t_point	**points;
// 	int		i;

// 	i = 1;
// 	while (env->point_set->points[i])
// 	{
// 		draw_segment(env, env->point_set->points[i - 1], env->point_set->points[i]);
// 		i++;
// 	}
// 	env->point_set = env->point_set->next;
// 	while (env->point_set)
// 	{
// 		draw_segment(env, env->point_set->prev->points[0], env->point_set->points[0]);
// 		i = 1;
// 		while (env->point_set->points[i])
// 		{
// 			draw_segment(env, env->point_set->points[i - 1], env->point_set->points[i]);
// 			draw_segment(env, env->point_set->prev->points[i], env->point_set->points[i]);
// 			i++;
// 		}
// 		env->point_set = env->point_set->next;
// 	}
// }

// void	draw_point_set(t_env *env)
// {
// 	t_point	**points;
// 	int		i;

// 	while (env->point_set)
// 	{
// 		i = 0;
// 		while (env->point_set->points[i])
// 		{
// 			draw_point(env, env->point_set->points[i], env->color);
// 			if (i > 0)
// 				draw_segment(env, env->point_set->points[i - 1], env->point_set->points[i], RED);
// 			if (env->point_set->prev)
// 				draw_segment(env, env->point_set->prev->points[i], env->point_set->points[i], RED);
// 			i++;
// 		}
// 		env->point_set = env->point_set->next;
// 	}
// }

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
	draw_axis(env, WHITE);
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

void	draw_segment(t_env *env, t_point *p1, t_point *p2)
{
	int 	x1;
	int 	y1;
	int 	x2;
	int 	y2;
	double	t;
	int		color;

	if (p1->z > p2->z)
		ft_swap(&p1, &p2);
	x1 = get_2d_x(env, p1);
	y1 = get_2d_y(env, p1);
	x2 = get_2d_x(env, p2);
	y2 = get_2d_y(env, p2);
	color = env->color + p2->z;
	t = -1.00;
	while (t <= 0)
	{
		mlx_pixel_put(env->mlx, env->window, (x1 - x2) * t + x1, (y1 - y2) * t + y1, color);
		if (color + 1 <= 0xFFFFFF)
			color += 1;
		t += 0.001;
	}
}
