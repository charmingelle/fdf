#include "header.h"

int		main(int argc, char **argv)
{
	t_env	*env;
	int		fd;

	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
			exit(1);
		env = get_env(fd);
		close(fd);
		draw_axis(env, WHITE);
		draw(env);
		mlx_hook(env->window, 2, 0, handle_key_press, env);
		mlx_hook(env->window, 17, 0, (int (*)())&exit, env);
		mlx_mouse_hook(env->window, &mouse_handle, env);
		mlx_loop(env->mlx);
	}
}

t_env	*get_env(int fd)
{
	t_env	*env;

	if (!(env = (t_env *)malloc(sizeof(t_env))))
		exit(1);
	if (!(env->mlx = mlx_init()))
		exit(1);
	env->w_width = 1400;
	env->w_height = 1200;
	env->seglen = 15;
	if (!(env->window = mlx_new_window(env->mlx, env->w_width, env->w_height, "FDF")))
		exit(1);
	set_figure(fd, env);
	center_figure(env);
	env->color = GREEN;
	env->angle_x = 0;
	env->angle_y = 0;
	env->angle_z = 0;
	return (env);
}

void	center_figure(t_env *env)
{
	t_point_row	*ps;
	double		x_center;
	double		y_center;
	int 		i;

	ps = env->pointset;
	x_center = -((double)env->f_width - 1) / 2;
	y_center = -((double)env->f_height - 1) / 2;
	while (ps)
	{
		i = 0;
		while (ps->points[i])
		{
			move_point(ps->points[i], x_center, y_center);
			i++;
		}
		ps = ps->next;
	}
}

int		handle_key_press(int keycode, t_env *env)
{
	int	change_flag;

	change_flag = 0;
	keycode == ESC ? exit(0) : 0;
	keycode == A && ++change_flag ? (env->angle_y += DEGREE5) : 0;
	keycode == D && ++change_flag ? (env->angle_y -= DEGREE5) : 0;
	keycode == W && ++change_flag ? (env->angle_x -= DEGREE5) : 0;
	keycode == S && ++change_flag ? (env->angle_x += DEGREE5) : 0;
	keycode == Q && ++change_flag ? (env->angle_z += DEGREE5) : 0;
	keycode == E && ++change_flag ? (env->angle_z -= DEGREE5) : 0;
	change_flag ? draw_axis(env, WHITE) : 0;
	change_flag ? draw(env) : 0;
	return (0);
}

int		mouse_handle(int key, int x, int y, t_env *env)
{
	if (key == 4)
	{
		env->seglen < 120 ? env->seglen += 5 : 0;
		draw_axis(env, WHITE);
		draw(env);
	}
	else if (key == 5)
	{
		env->seglen > 1 ? env->seglen -= 5 : 0;
		draw_axis(env, WHITE);
		draw(env);
	}
	return (0);
}
