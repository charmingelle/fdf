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
				a = get_modified_point(env, ps->points[i - 1]);
				b = get_modified_point(env, ps->points[i]);
				c = get_modified_point(env, ps->next->points[i]);
				d = get_modified_point(env, ps->next->points[i - 1]);
				draw_seg(env, &a, &b);
				draw_seg(env, &b, &c);
				draw_seg(env, &c, &d);
				draw_seg(env, &d, &a);
				draw_triangle(env, &a, &b, &c);
				draw_triangle(env, &a, &d, &c);
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
	t_point	temp1;
	t_point	temp2;
	double	t;
	double	step;

	step = 0.5 / fabs(middle->y - top->y);
	t = 0;
	while (t <= 1)
	{
		temp1.x = (middle->x - top->x) * t + top->x;
		temp1.y = (middle->y - top->y) * t + top->y;
		temp1.z = (middle->z - top->z) * t + top->z;
		temp1.color = (middle->color - top->color) * t + top->color;
		temp2.x = (bottom->x - top->x) * t + top->x;
		temp2.y = (bottom->y - top->y) * t + top->y;
		temp2.z = (bottom->z - top->z) * t + top->z;
		temp2.color = (bottom->color - top->color) * t + top->color;
		draw_seg(env, &temp1, &temp2);
		t += step;
	}
}

void	draw_middle_bottom_half_triangle(t_env *env, t_point *top, t_point *middle, t_point *bottom)
{
	t_point	temp1;
	t_point	temp2;
	double	t;
	double	step;
	
	step = 0.5 / fabs(bottom->y - middle->y);
	t = 0;
	while (t <= 1)
	{
		temp1.x = (middle->x - bottom->x) * t + bottom->x;
		temp1.y = (middle->y - bottom->y) * t + bottom->y;
		temp1.z = (middle->z - bottom->z) * t + bottom->z;
		temp1.color = (middle->color - bottom->color) * t + bottom->color;
		temp2.x = (top->x - bottom->x) * t + bottom->x;
		temp2.y = (top->y - bottom->y) * t + bottom->y;
		temp2.z = (top->z - bottom->z) * t + bottom->z;
		temp2.color = (top->color - bottom->color) * t + bottom->color;
		draw_seg(env, &temp1, &temp2);
		t += step;
	}
}

void	draw_seg(t_env *env, t_point *p1, t_point *p2)
{
	double	step;
	double	t;
	int		x;
	int		y;
	double	z;
	int		color;

	step = 0.5 / sqrt(pow(p1->x - p2->x, 2) + pow(p1->y - p2->y, 2));
	t = 0;
	while (t <= 1)
	{
		x = (p2->x - p1->x) * t + p1->x;
		y = (p2->y - p1->y) * t + p1->y;
		z = (p2->z - p1->z) * t + p1->z;
		color = (p2->color - p1->color) * t + p1->color;
		if ((x > 0 &&  x < env->w_width && y > 0 && y < env->w_height)
			&& (!env->z_buff[y][x].color || z > env->z_buff[y][x].z))
		{
			env->z_buff[y][x] = (t_z_buff_elem){.z = z, .color = color};
			mlx_pixel_put(env->mlx, env->window, x, y, color);
		}
		t += step;
	}
}
