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

static void	draw_seg(t_env *env, t_point *p1, t_point *p2)
{
	double	step;
	double	t;
	int		x;
	int		y;
	double	z;

	step = 0.5 / sqrt(pow(p1->x - p2->x, 2) + pow(p1->y - p2->y, 2));
	t = 0;
	while (t <= 1)
	{
		x = (p2->x - p1->x) * t + p1->x;
		y = (p2->y - p1->y) * t + p1->y;
		z = (p2->z - p1->z) * t + p1->z;
		if ((x > 0 && x < env->wwidth && y > 0 && y < env->wheight)
			&& (!env->z_buff[y][x].color || z > env->z_buff[y][x].z))
		{
			env->z_buff[y][x] = (t_z_buff_elem){.z = z,
				.color = (p2->color - p1->color) * t + p1->color};
			mlx_pixel_put(env->mlx, env->window, x, y,
				(p2->color - p1->color) * t + p1->color);
		}
		t += step;
	}
}

static void	draw_mid_bot_triang(t_env *env, t_point *top,
	t_point *mid, t_point *bot)
{
	t_point	temp1;
	t_point	temp2;
	double	t;
	double	step;

	step = 0.5 / fabs(bot->y - mid->y);
	t = 0;
	while (t <= 1)
	{
		temp1.x = (mid->x - bot->x) * t + bot->x;
		temp1.y = (mid->y - bot->y) * t + bot->y;
		temp1.z = (mid->z - bot->z) * t + bot->z;
		temp1.color = (mid->color - bot->color) * t + bot->color;
		temp2.x = (top->x - bot->x) * t + bot->x;
		temp2.y = (top->y - bot->y) * t + bot->y;
		temp2.z = (top->z - bot->z) * t + bot->z;
		temp2.color = (top->color - bot->color) * t + bot->color;
		draw_seg(env, &temp1, &temp2);
		t += step;
	}
}

static void	draw_top_mid_triang(t_env *env, t_point *top,
	t_point *mid, t_point *bot)
{
	t_point	temp1;
	t_point	temp2;
	double	t;
	double	step;

	step = 0.5 / fabs(mid->y - top->y);
	t = 0;
	while (t <= 1)
	{
		temp1.x = (mid->x - top->x) * t + top->x;
		temp1.y = (mid->y - top->y) * t + top->y;
		temp1.z = (mid->z - top->z) * t + top->z;
		temp1.color = (mid->color - top->color) * t + top->color;
		temp2.x = (bot->x - top->x) * t + top->x;
		temp2.y = (bot->y - top->y) * t + top->y;
		temp2.z = (bot->z - top->z) * t + top->z;
		temp2.color = (bot->color - top->color) * t + top->color;
		draw_seg(env, &temp1, &temp2);
		t += step;
	}
}

static void	draw_triang(t_env *env, t_point *a, t_point *b, t_point *c)
{
	t_point	p[3];

	p[0] = *a;
	p[1] = *b;
	p[2] = *c;
	sort(p);
	p[0].y != p[1].y ? draw_top_mid_triang(env, &p[0], &p[1], &p[2]) : 0;
	p[1].y != p[2].y ? draw_mid_bot_triang(env, &p[0], &p[1], &p[2]) : 0;
}

static void	draw_segs_and_triags(t_env *env)
{
	t_point_row	*ps;
	int			i;
	t_point		rect[4];

	ps = env->pointset;
	while (ps)
	{
		i = 0;
		while (ps->points[++i])
			if (ps->next)
			{
				rect[0] = get_modified_point(env, ps->points[i - 1]);
				rect[1] = get_modified_point(env, ps->points[i]);
				rect[2] = get_modified_point(env, ps->next->points[i]);
				rect[3] = get_modified_point(env, ps->next->points[i - 1]);
				draw_seg(env, &rect[0], &rect[1]);
				draw_seg(env, &rect[1], &rect[2]);
				draw_seg(env, &rect[2], &rect[3]);
				draw_seg(env, &rect[3], &rect[0]);
				env->bonus ? draw_triang(env, &rect[0], &rect[1], &rect[2]) : 0;
				env->bonus ? draw_triang(env, &rect[0], &rect[3], &rect[2]) : 0;
			}
		ps = ps->next;
	}
}

void		draw(t_env *env)
{
	clear_z_buffer(env);
	mlx_clear_window(env->mlx, env->window);
	draw_segs_and_triags(env);
}
