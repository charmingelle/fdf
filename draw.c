#include "header.h"

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
	x1 = (*p1)->x + env->width / 2;
	y1 = -(*p1)->y + env->height / 2;
	x2 = (*p2)->x + env->width / 2;
	y2 = -(*p2)->y + env->height / 2;
	color = env->color;
	t = -1.00;
	while (t <= 0)
	{
		mlx_pixel_put(env->mlx, env->window, (x1 - x2) * t + x1, (y1 - y2) * t + y1, color);
		t += 0.001;
		// t += 0.01;
	}
	free(*p1);
	free(*p2);
}
