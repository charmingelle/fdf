/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 14:11:15 by grevenko          #+#    #+#             */
/*   Updated: 2017/12/21 20:14:57 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	ft_clear_buffer(t_env *env)
{
	int	x;
	int	y;

	y = -1;
	while (++y < env->w_height && (x = -1))
		while (++x < env->w_width)
			env->z_buff[y][x] = (t_z_buff_elem){0, 0};
}

void	draw(t_env *env)
{
	ft_clear_buffer(env);
	mlx_clear_window(env->mlx, env->window);
	draw_segs_and_triags(env);
}

void	draw_segs_and_triags(t_env *env)
{
	t_point_row	*ps;
	int			i;
	t_point		a;
	t_point		b;
	t_point		c;
	t_point		d;

	ps = env->pointset;
	while (ps)
	{
		i = 0;
		while (ps->points[++i])
		{
			if (ps->next)
			{
				a = get_rot_and_exp_point(env, ps->points[i - 1]);
				b = get_rot_and_exp_point(env, ps->points[i]);
				c = get_rot_and_exp_point(env, ps->next->points[i]);
				d = get_rot_and_exp_point(env, ps->next->points[i - 1]);
				draw_triangle(env, &a, &b, &c);
				draw_triangle(env, &a, &d, &c);
				draw_seg(env, &a, &b);
				draw_seg(env, &b, &c);
				draw_seg(env, &c, &d);
				draw_seg(env, &d, &a);
			}
		}
		ps = ps->next;
	}
}

void	sort(t_point *array)
{
	int		i;
	int		j;
	t_point	tmp;

	i = -1;
	while (++i < 3)
	{
		j = i - 1;
		while (++j < 3)
			if (array[j].y > array[i].y)
			{
				tmp = array[j];
				array[j] = array[i];
				array[i] = tmp;
			}
	}
}

void	draw_triangle(t_env *env, t_point *a, t_point *b, t_point *c)
{
	t_point	p[3];

	p[0] = *a;
	p[1] = *b;
	p[2] = *c;
	sort(p);
	p[0].y != p[1].y ? draw_top_middle_half_triangle(env, &p[0], &p[1], &p[2]) : 0;
	p[1].y != p[2].y ? draw_middle_bottom_half_triangle(env, &p[0], &p[1], &p[2]) : 0;
}

void	draw_top_middle_half_triangle(t_env *env, t_point *top, t_point *middle, t_point *bottom)
{
	int	y;
	int	y_limit;
	int	x_start;
	int	x_end;
	int temp;
	double z;

	y = top->y + (env->w_height / 2) + 1;
	y_limit = middle->y + (env->w_height / 2);
	while (--y > y_limit)
	{
		x_start = count_x_on_seg(env, top, middle, y);
		x_end = count_x_on_seg(env, top, bottom, y);
		if (x_start > x_end)
		{
			temp = x_start;
			x_start = x_end;
			x_end = temp;
		}
		while (x_start < x_end)
		{
			z = (middle->z - top->z) * (x_start - top->x + (env->w_height / 2)) / (middle->x + (env->w_height / 2) - top->x + (env->w_height / 2)) + top->z;
			if (y >=0 && x_start >= 0 && y < env->w_height && x_start < env->w_width && (!env->z_buff[y][x_start].color
				|| env->z_buff[y][x_start].z < z))
			{
				env->z_buff[y][x_start] = (t_z_buff_elem){.z = z, .color = RED};
				// mlx_pixel_put(env->mlx, env->window, x_start, y, RED);
			}
			x_start++;
		}
	}
}

void	draw_middle_bottom_half_triangle(t_env *env, t_point *top, t_point *middle, t_point *bottom)
{
	int	y;
	int	y_limit;
	int	x_start;
	int	x_end;
	int temp;
	double	z;
	
	y = middle->y + (env->w_height / 2) + 1;
	y_limit = bottom->y + (env->w_height / 2);
	while (--y > y_limit)
	{
		x_start = count_x_on_seg(env, middle, bottom, y);
		x_end = count_x_on_seg(env, top, bottom, y);
		if (x_start > x_end)
		{
			temp = x_start;
			x_start = x_end;
			x_end = temp;
		}
		while (x_start < x_end)
		{
			z = (bottom->z - middle->z) * (x_start - middle->x + (env->w_height / 2)) / (bottom->x + (env->w_height / 2) - middle->x + (env->w_height / 2)) + middle->z;
			if (y >=0 && x_start >= 0 && y < env->w_height && x_start < env->w_width && (!env->z_buff[y][x_start].color
				|| env->z_buff[y][x_start].z < z))
			{
				env->z_buff[y][x_start] = (t_z_buff_elem){.z = z, .color = RED};
				// mlx_pixel_put(env->mlx, env->window, x_start, y, RED);
			}
			x_start++;
		}
	}
}

int	count_x_on_seg(t_env *env, t_point *start, t_point *end, double y)
{
	double	x_start;
	double	y_start;
	double	x_end;
	double	y_end;

	x_start = start->x + env->w_width / 2;
	y_start = start->y + env->w_height / 2;
	x_end = end->x + env->w_width / 2;
	y_end = end->y + env->w_height / 2;
	// printf("%f - %f - %f - %f\n", x_start, y_start, x_end, y_end);
	return (((x_start - x_end) * y + x_end * y_start - y_end * x_start) / (y_start - y_end));
}

void	draw_seg(t_env *env, t_point *p1, t_point *p2)
{
	double	x1;
	double	y1;
	double	x2;
	double	y2;
	double	t;
	double	step;
	double	z;
	int	y;
	int	x;

	x1 = p1->x + env->w_width / 2;
	y1 = p1->y + env->w_height / 2;
	x2 = p2->x + env->w_width / 2;
	y2 = p2->y + env->w_height / 2;
	step = 1.0 / sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
	t = 0;
	while (t <= 1)
	{
		x = (x2 - x1) * t + x1;
		y = (y2 - y1) * t + y1;
		z = (p2->z - p1->z) * t + p1->z;
		if (y >=0 && x >= 0 && y < env->w_height && x < env->w_width && (!env->z_buff[y][x].color
				|| env->z_buff[y][x].z < z))
		{
			env->z_buff[y][x] = (t_z_buff_elem){.z = z, .color = RED};
			mlx_pixel_put(env->mlx, env->window, x, y, env->color);
		}
		t += step;
	}
}
