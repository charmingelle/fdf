#include "header.h"

int		handle_key_press(int keycode, t_env *env)
{
	if (keycode == ESC)
		exit(0);
	else if (keycode == A)
	{
		env->angle_y += DEGREE5;
		draw(env);
	}
	else if (keycode == D)
	{
		env->angle_y -= DEGREE5;
		draw(env);
	}
	else if (keycode == W)
	{
		env->angle_x += DEGREE5;
		draw(env);
	}
	else if (keycode == S)
	{
		env->angle_x -= DEGREE5;
		draw(env);
	}
	else if (keycode == Q)
	{
		env->angle_z -= DEGREE5;
		draw(env);
	}
	else if (keycode == E)
	{
		env->angle_z += DEGREE5;
		draw(env);
	}
	return (0);
}

t_env	*get_env(int fd)
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
	env->point_set = get_point_set(fd, &width, &height);
	
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

	// Test seg and flat cross
	// t_seg		*s;
	// t_flat			*f;
	// t_point			**cross;
	// s = (t_seg *)malloc(sizeof(t_seg));
	// f = (t_flat *)malloc(sizeof(t_flat));
	// f->a = get_point(0, 0, 0);
	// f->b = get_point(2, 0, 0);
	// f->c = get_point(2, 2, 0);
	// f->d = get_point(0, 2, 0);
	// s->a = get_point(0, 0, 0);
	// s->b = get_point(2, 2, 0);
	// cross = get_seg_flat_cross(s, f);
	// if (*cross == NULL)
	// 	printf("%p\n", *cross);
	// while (*cross)
	// 	print_point(*cross++);

	// // Test segs cross
	// t_seg	*s1;
	// t_seg	*s2;
	// t_point		*cross;
	// s1 = (t_seg *)malloc(sizeof(t_seg));
	// s2 = (t_seg *)malloc(sizeof(t_seg));
	// s1->a = get_point(-1, -1, 0);
	// s1->b = get_point(4, 4, 0);
	// s2->a = get_point(3, -3, 0);
	// s2->b = get_point(3, 4, 0);
	// cross = get_flat_seg_cross(s1->a, s1->b, s2->a, s2->b);
	// if (cross == NULL)
	// 	printf("%p\n", cross);
	// else
	// 	print_point(cross);

	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
			exit(1);
		env = get_env(fd);
		close(fd);
		// draw_axis(env, WHITE);
		draw(env);

		mlx_hook(env->window, 2, 0, handle_key_press, env);
		mlx_hook(env->window, 17, 0, (int (*)())&exit, env);
		mlx_loop(env->mlx);
	}
}
