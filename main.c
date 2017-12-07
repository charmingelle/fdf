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
	env->width = 800;
	env->height = 600;
	if (!(env->window = mlx_new_window(env->mlx, env->width, env->height, "FDF")))
		exit(1);
	env->point_set = create_point_set(fd);
	env->color = LIME;
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
	// draw_point_set(env);

	// int		radius;
	// int		diag;
	// t_point	**point_set;
	// int		point_set_size;

	// env = (t_env *)malloc(sizeof(t_env));
	// env->mlx = mlx_init();
	// if (env->mlx == NULL)
	// 	return (1);
	// env->width = 800;
	// env->height = 600;
	// env->window = mlx_new_window(env->mlx, env->width, env->height, "Rotation");
	// if (env->window == NULL)
	// 	return (1);
	// env->point_set_size = 8;
	// env->point_set = (t_point **)malloc(sizeof(t_point *) * 8);

	// radius = 100;
	// diag = radius/sqrt(2);
	// env->point_set[0] = create_point(radius, 0, 30);
	// env->point_set[1] = create_point(diag, diag, 30);
	// env->point_set[2] = create_point(0, radius, 30);
	// env->point_set[3] = create_point(-diag, diag, 30);
	// env->point_set[4] = create_point(-radius, 0, 30);
	// env->point_set[5] = create_point(-diag, -diag, 30);
	// env->point_set[6] = create_point(0, -radius, 30);
	// env->point_set[7] = create_point(diag, -diag, 30);
	// env->color = LIME;
	
	draw_axis(env, WHITE);
	// draw_point_set(env);


	// draw_segment(env, env->point_set[0], env->point_set[0], LIME);
	// draw_graph(env, &square_function, -100, 100, RED);

	// t_point *point1 = create_point(0, 0, 0);
	// draw_point(env, point1, WHITE);
	// t_point *point2 = create_point(100, 0, 0);
	// draw_point(env, point1, WHITE);
	// t_point *point3 = create_point(0, 100, 0);
	// draw_point(env, point1, WHITE);
	// t_point *point4 = create_point(0, 0, 100);
	// draw_point(env, point1, WHITE);

	// int		xpm_width = 48;
	// int		xpm_height = 48;
	// void	*image = mlx_xpm_file_to_image(env->mlx, argv[1], &xpm_width, &xpm_height);
	// printf("image = %p\n", image);
	// if (image != NULL)
	// 	mlx_put_image_to_window(env->mlx, env->window, image, 10, 10);

	mlx_key_hook(env->window, handle_key_press, env);
	mlx_loop(env->mlx);
}
