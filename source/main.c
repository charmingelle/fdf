/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/29 14:43:20 by grevenko          #+#    #+#             */
/*   Updated: 2017/12/29 14:46:35 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void					draw(t_env *env)
{
	clear_z_buffer(env);
	mlx_clear_window(env->mlx, env->window);
	draw_segs_and_triags(env);
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
	env.shift_x = env.wwidth / 2;
	env.shift_y = env.wheight / 2;
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
