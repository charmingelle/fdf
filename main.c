#include "header.h"

t_point *create_point(int x, int y, int z)
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
		draw_rotated(env, rotate_point_y, -1);
	else if (keycode == D)
		draw_rotated(env, rotate_point_y, 1);
	else if (keycode == W)
		draw_rotated(env, rotate_point_x, -1);
	else if (keycode == S)
		draw_rotated(env, rotate_point_x, 1);
	else if (keycode == Q)
		draw_rotated(env, rotate_point_z, -1);
	else if (keycode == E)
		draw_rotated(env, rotate_point_z, 1);
	return (0);
}

t_env	*create_env(int fd)
{
	t_env	*env;

	if (!(env = (t_env *)malloc(sizeof(t_env))))
		exit(1);
	if (!(env->mlx = mlx_init()))
		exit(1);
	env->width = 1400;
	env->height = 1200;
	if (!(env->window = mlx_new_window(env->mlx, env->width, env->height, "FDF")))
		exit(1);
	env->point_set = create_point_set(fd);
	env->color = GREEN;
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
	draw_point_set(env);

	mlx_key_hook(env->window, handle_key_press, env);
	mlx_loop(env->mlx);
}
