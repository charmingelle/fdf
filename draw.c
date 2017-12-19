/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 14:11:15 by grevenko          #+#    #+#             */
/*   Updated: 2017/12/19 20:27:31 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	draw(t_env *env)
{
	mlx_clear_window(env->mlx, env->window);
	draw_segs_and_triags(env);
}

void	draw_segs_and_triags(t_env *env)
{
	t_point_row	*ps;
	int			i;
	t_point		*a;
	t_point		*b;
	t_point		*c;
	t_point		*d;

	ps = env->pointset;
	while (ps)
	{
		i = -1;
		while (ps->points[++i])
		{
			if (i >= 1 && ps->next)
			{
				a = get_rot_and_exp_point(env, ps->points[i - 1]);
				b = get_rot_and_exp_point(env, ps->points[i]);
				c = get_rot_and_exp_point(env, ps->next->points[i]);
				d = get_rot_and_exp_point(env, ps->next->points[i - 1]);
				draw_triangle(env, a, b, c);
				draw_triangle(env, a, d, c);				
				draw_seg(env, a, b);
				draw_seg(env, b, c);
				draw_seg(env, c, d);
				draw_seg(env, d, a);
			}
		}
		ps = ps->next;
	}
}

void	draw_triangle(t_env *env, t_point *a, t_point *b, t_point *c)
{
	if (a->y < b->y)
		point_swap(a, b);
	if (a->y < c->y)
		point_swap(a, c);
    if (b->y < c->y)
    	point_swap(b, c);
	a->y != b->y ? draw_top_middle_half_triangle(env, a, b, c) : 0;
	b->y != c->y ? draw_middle_bottom_half_triangle(env, a, b, c) : 0;
}

void	draw_top_middle_half_triangle(t_env *env, t_point *top, t_point *middle, t_point *bottom)
{
	printf("part1\n");
	double	y;
	double	y_limit;
	double	x_start;
	double	x_end;
	
	y = top->y + (env->w_height / 2) + 1;
	y_limit = middle->y + (env->w_height / 2);
	while (y > y_limit)
	{
		x_start = count_x_on_seg(env, top, middle, y);
		x_end = count_x_on_seg(env, top, bottom, y);
		if (x_start > x_end)
			double_swap(&x_start, &x_end);
		while (x_start < x_end)
		{
			mlx_pixel_put(env->mlx, env->window, x_start, y, RED);
			x_start++;
		}
		y--;
	}
}

void	draw_middle_bottom_half_triangle(t_env *env, t_point *top, t_point *middle, t_point *bottom)
{
	double	y;
	double	y_limit;
	double	x_start;
	double	x_end;
	
	y = middle->y + (env->w_height / 2) + 1;
	y_limit = bottom->y + (env->w_height / 2);
	while (y > y_limit)
	{
		x_start = count_x_on_seg(env, middle, bottom, y);
		x_end = count_x_on_seg(env, top, bottom, y);
		if (x_start > x_end)
			double_swap(&x_start, &x_end);
		while (x_start < x_end)
		{
			mlx_pixel_put(env->mlx, env->window, x_start, y, RED);
			x_start++;
		}
		y--;
	}
}

double	count_x_on_seg(t_env *env, t_point *start, t_point *end, double y)
{
	double	x_start;
	double	y_start;
	double	x_end;
	double	y_end;

	x_start = start->x + env->w_width / 2;
	y_start = start->y + env->w_height / 2;
	x_end = end->x + env->w_width / 2;
	y_end = end->y + env->w_height / 2;
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

	x1 = p1->x + env->w_width / 2;
	y1 = p1->y + env->w_height / 2;
	x2 = p2->x + env->w_width / 2;
	y2 = p2->y + env->w_height / 2;
	step = 1.0 / sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
	t = 0;
	while (t <= 1)
	{
		mlx_pixel_put(env->mlx, env->window, (x2 - x1) * t + x1,
			(y2 - y1) * t + y1, env->color);
		t += step;
	}
}
