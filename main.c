#include "header.h"

t_point *create_point(double x, double y, double z)
{
	t_point *point;

	point = (t_point *)malloc(sizeof(t_point));
	point->x = x;
	point->y = y;
	point->z = z;
	return (point);
}

int		handle_key_press(int keycode, t_env *env)
{
	if (keycode == ESC)
		exit(0);
	else if (keycode == A)
	{
		env->angle_x += DEGREE5;
		mlx_clear_window(env->mlx, env->window);
		draw_axis(env, WHITE);
		draw(env);
	}
	else if (keycode == D)
	{
		env->angle_x -= DEGREE5;
		mlx_clear_window(env->mlx, env->window);
		draw_axis(env, WHITE);
		draw(env);
	}
	else if (keycode == W)
	{
		env->angle_y -= DEGREE5;
		mlx_clear_window(env->mlx, env->window);
		draw_axis(env, WHITE);
		draw(env);
	}
	else if (keycode == S)
	{
		env->angle_y += DEGREE5;
		mlx_clear_window(env->mlx, env->window);
		draw_axis(env, WHITE);
		draw(env);
	}
	else if (keycode == Q)
	{
		env->angle_z -= DEGREE5;
		mlx_clear_window(env->mlx, env->window);
		draw_axis(env, WHITE);
		draw(env);
	}
	else if (keycode == E)
	{
		env->angle_z += DEGREE5;
		mlx_clear_window(env->mlx, env->window);
		draw_axis(env, WHITE);
		draw(env);
	}
	return (0);
}

t_env	*create_env(int fd)
{
	t_env	*env;
	int		width;
	int		height;

	if (!(env = (t_env *)malloc(sizeof(t_env))))
		exit(1);
	if (!(env->mlx = mlx_init()))
		exit(1);
	env->width = 1400;
	env->height = 1200;
	if (!(env->window = mlx_new_window(env->mlx, env->width, env->height, "FDF")))
		exit(1);
	env->point_set = create_point_set(fd, &width, &height);
	env->figure_width = width;
	env->figure_height = height;
	env->color = GREEN;
	env->angle_x = 0;
	env->angle_y = 0;
	env->angle_z = 0;
	return (env);
}

int		main(int argc, char **argv)
{
	t_env	*env;
	int		fd;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		exit(1);
	env = create_env(fd);
	close(fd);
	draw_axis(env, WHITE);
	draw(env);

	mlx_key_hook(env->window, handle_key_press, env);
	mlx_loop(env->mlx);
}
