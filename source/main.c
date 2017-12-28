/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 14:11:15 by grevenko          #+#    #+#             */
/*   Updated: 2017/12/22 13:24:51 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int				mouse_handle(int key, int x, int y, t_env *env)
{
	x = 0;
	y = 0;
	if (key == 4)
	{
		env->seglen < 120 ? env->seglen += 1 : 0;
		draw(env);
	}
	else if (key == 5)
	{
		env->seglen > 1 ? env->seglen -= 1 : 0;
		draw(env);
	}
	return (0);
}

static int				handle_key_press(int keycode, t_env *env)
{
	int	change_flag;

	change_flag = 0;
	keycode == ESC ? exit(0) : 0;
	keycode == A && ++change_flag ? (env->ang_y = (env->ang_y + 5) % 360) : 0;
	keycode == D && ++change_flag ? (env->ang_y = (env->ang_y - 5) % 360) : 0;
	keycode == W && ++change_flag ? (env->ang_x = (env->ang_x - 5) % 360) : 0;
	keycode == S && ++change_flag ? (env->ang_x = (env->ang_x + 5) % 360) : 0;
	keycode == Q && ++change_flag ? (env->ang_z = (env->ang_z + 5) % 360) : 0;
	keycode == E && ++change_flag ? (env->ang_z = (env->ang_z - 5) % 360) : 0;
	keycode == ARROW_LEFT && ++change_flag ? (env->shift_x -= 5) : 0;	
	keycode == ARROW_RIGHT && ++change_flag ? (env->shift_x += 5) : 0;
	keycode == ARROW_UP && ++change_flag ? (env->shift_y -= 5) : 0;
	keycode == ARROW_DOWN && ++change_flag ? (env->shift_y += 5) : 0;
	change_flag ? draw(env) : 0;
	return (0);
}

static t_z_buff_elem	**init_z_buff(t_env env)
{
	t_z_buff_elem	**z_buff;
	int				y;

	if (!(z_buff = (t_z_buff_elem **)malloc(sizeof(t_z_buff_elem *)
		* env.wheight)))
		exit(show_malloc_error());
	y = -1;
	while (++y < env.wheight)
		if (!(z_buff[y] = (t_z_buff_elem *)malloc(sizeof(t_z_buff_elem)
			* env.wwidth)))
			exit(show_malloc_error());
	return (z_buff);
}

static void				center_figure(t_env *env)
{
	t_point_row	*ps;
	double		x_center;
	double		y_center;
	int			i;

	ps = env->pointset;
	x_center = -((double)env->fwidth - 1) / 2;
	y_center = -((double)env->fheight - 1) / 2;
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

static t_env			get_env(int fd, int serf)
{
	t_env	env;

	if (!(env.mlx = mlx_init()))
		exit(1);
	env.wwidth = 1200;
	env.wheight = 900;
	env.seglen = 15;
	if (!(env.window = mlx_new_window(env.mlx, env.wwidth, env.wheight,
		"FDF")))
		exit(1);
	set_figure(fd, &env);
	center_figure(&env);
	env.z_buff = init_z_buff(env);
	env.ang_x = 0;
	env.ang_y = 0;
	env.ang_z = 0;
	env.shift_x = 0;
	env.shift_y = 0;
	env.serf = serf;
	return (env);
}

int						main(int argc, char **argv)
{
	t_env	env;
	int		fd;
	int		serf;

	if (argc == 1 || (argc == 3 && ft_strcmp(argv[1], "-s")) || argc > 3)
		write(1, "usage: ./fdf [-s] file_name\n", 28);
	else
	{
		serf = 0;
		if (argc == 2)
			fd = open(argv[1], O_RDONLY);
		else
		{
			fd = open(argv[2], O_RDONLY);
			serf = 1;
		}
		(fd == -1) ? exit(show_invalid_file_error()) : 0;
		env = get_env(fd, serf);
		close(fd);
		draw(&env);
		mlx_hook(env.window, 2, 0, handle_key_press, &env);
		mlx_hook(env.window, 17, 0, (int (*)())&exit, &env);
		mlx_mouse_hook(env.window, &mouse_handle, &env);
		mlx_loop(env.mlx);
	}
}
