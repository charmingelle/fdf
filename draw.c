/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 14:11:15 by grevenko          #+#    #+#             */
/*   Updated: 2017/12/19 19:17:54 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	draw(t_env *env)
{
	t_flat		*flats;

	mlx_clear_window(env->mlx, env->window);
	define_flats(env, &flats);
	draw_flats(env, &flats);
	free_flats(&flats);
}

void	define_flats(t_env *env, t_flat **flats)
{
	t_point_row	*ps;
	int			i;

	*flats = NULL;
	ps = env->pointset;
	while (ps)
	{
		i = -1;
		while (ps->points[++i])
		{
			if (i >= 1 && ps->next)
				add_flat(flats, get_flat(get_rot_and_exp_point(env, ps->points[i - 1]),
					get_rot_and_exp_point(env, ps->points[i]),
					get_rot_and_exp_point(env, ps->next->points[i]),
					get_rot_and_exp_point(env, ps->next->points[i - 1])));
		}
		ps = ps->next;
	}
}

void	draw_flats(t_env *env, t_flat **flats)
{
	while (*flats)
	{
		draw_flat(env, *flats);
		flats = &((*flats)->next);
	}
}

void	draw_flat(t_env *env, t_flat *flat)
{
	draw_seg(env, flat->a, flat->b);
	draw_seg(env, flat->b, flat->c);
	draw_seg(env, flat->c, flat->d);
	draw_seg(env, flat->d, flat->a);
	draw_triangle(env, flat->a, flat->b, flat->c);
	draw_triangle(env, flat->c, flat->d, flat->a);
}

void	draw_triangle(t_env *env, t_point *a, t_point *b, t_point *c)
{
	t_point	**points;

	points = (t_point **)malloc(sizeof(t_point *) * 3);
	points[0] = a;
	points[1] = b;
	points[2] = c;
	order_triang_points(points);
	points[0]->y != points[1]->y ? draw_top_middle_half_triangle(env, points) : 0;
	points[1]->y != points[2]->y ? draw_middle_bottom_half_triangle(env, points) : 0;
	free(points);
}

void	draw_top_middle_half_triangle(t_env *env, t_point **points)
{
	double	y;
	double	y_limit;
	double	x_start;
	double	x_end;
	
	y = points[0]->y + (env->w_height / 2) + 1;
	y_limit = points[1]->y + (env->w_height / 2);
	while (y > y_limit)
	{
		x_start = count_x_on_seg(env, points[0], points[1], y);
		x_end = count_x_on_seg(env, points[0], points[2], y);
		if (x_start > x_end)
			ft_swap(&x_start, &x_end);
		while (x_start < x_end)
		{
			mlx_pixel_put(env->mlx, env->window, x_start, y, RED);
			x_start++;
		}
		y--;
	}
}

void	draw_middle_bottom_half_triangle(t_env *env, t_point **points)
{
	double	y;
	double	y_limit;
	double	x_start;
	double	x_end;
	
	y = points[1]->y + (env->w_height / 2) + 1;
	y_limit = points[2]->y + (env->w_height / 2);
	while (y > y_limit)
	{
		x_start = count_x_on_seg(env, points[1], points[2], y);
		x_end = count_x_on_seg(env, points[0], points[2], y);
		if (x_start > x_end)
			ft_swap(&x_start, &x_end);
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

void	order_triang_points(t_point **points)
{
	t_point	*temp;
	int		i;
	int		j;

	
	i = 0;
	while (i < 3)
	{
		j = i;
		while (j < 3)
		{
			if (points[j]->y > points[i]->y)
			{
				temp = points[j];
				points[j] = points[i];
				points[i] = temp;
			}
			j++;
		}
		i++;
	}
}

// void	draw(t_env *env)
// {
// 	t_seg		*segs;
// 	t_flat		*flats;

// 	mlx_clear_window(env->mlx, env->window);
// 	fill_segs_amd_flats(env, &segs, &flats);
// 	remove_invisible_segs(&segs, &flats);
// 	free_flats(&flats);
// 	draw_segs(env, segs);
// 	free_segs(&segs);
// }

// void	fill_segs_amd_flats(t_env *env, t_seg **segs, t_flat **flats)
// {
// 	t_point_row	*ps;
// 	int			i;

// 	*segs = get_seg(NULL, NULL);
// 	*flats = NULL;
// 	ps = env->pointset;
// 	while (ps)
// 	{
// 		i = -1;
// 		while (ps->points[++i])
// 		{
// 			if (i >= 1)
// 				add_seg(segs, get_seg(get_rot_and_exp_point(env, ps->points[i - 1]),
// 					get_rot_and_exp_point(env, ps->points[i])));
// 			if (ps->next)
// 				add_seg(segs, get_seg(get_rot_and_exp_point(env, ps->next->points[i]),
// 					get_rot_and_exp_point(env, ps->points[i])));
// 			if (i >= 1 && ps->next)
// 				add_flat(flats, get_flat(get_rot_and_exp_point(env, ps->points[i - 1]),
// 					get_rot_and_exp_point(env, ps->points[i]),
// 					get_rot_and_exp_point(env, ps->next->points[i]),
// 					get_rot_and_exp_point(env, ps->next->points[i - 1])));
// 		}
// 		ps = ps->next;
// 	}
// }

void	remove_invisible_segs(t_seg **segs, t_flat **flats)
{
	t_seg	*temp;

	temp = (*segs)->next;
	while (temp != *segs)
	{
		process_seg(segs, temp, flats);
		temp = temp->next;
	}
}

void	process_seg(t_seg **segs, t_seg *seg, t_flat **flats)
{
	t_point		**cross;

	while (*flats)
	{
		if (!flat_contains_seg(seg, *flats))
		{
			if (seg_inside_flat(seg, *flats) && seg_below_flat(seg, *flats))
				return (delete_seg(seg));
			if (seg_crosses_flat(seg, *flats))
			{
				cross = get_seg_flat_cross(seg, *flats);
				if (cross[0] && !cross[1])
				{
					if (!equal_points(seg->a, cross[0]) && !equal_points(cross[0], seg->b))
					{
						add_seg_back(segs, get_seg(seg->a, cross[0]));
						add_seg_back(segs, get_seg(cross[0], seg->b));
						return ;
					}
				}
				// else if (cross[0] && cross[1])
				// {
				// 	!equal_points(seg->a, cross[0]) ? add_seg_back(segs, get_seg(seg->a, cross[0])) : 0;
				// 	!equal_points(cross[0], cross[1]) ? add_seg_back(segs, get_seg(cross[0], cross[1])) : 0;
				// 	!equal_points(cross[1], seg->b) ? add_seg_back(segs, get_seg(cross[1], seg->b)) : 0;
				// 	return ;
				// }
			}
		}
		flats = &((*flats)->next);
	}
}

int		flat_contains_seg(t_seg *seg, t_flat *flat)
{
	return (seg_inside_flat_side(seg, flat->a, flat->b)
		|| seg_inside_flat_side(seg, flat->b, flat->c)
		|| seg_inside_flat_side(seg, flat->c, flat->d)
		|| seg_inside_flat_side(seg, flat->d, flat->a));
}

int		seg_inside_flat_side(t_seg *seg, t_point *side_start, t_point *side_end)
{
	return (dist(side_start, seg->a) + dist(seg->a, side_end) == dist(side_start, side_end)
		&& dist(side_start, seg->b) + dist(seg->b, side_end) == dist(side_start, side_end));
}

int		seg_inside_flat(t_seg *seg, t_flat *flat)
{
	return (point_inside_flat(seg->a, flat)
		&& point_inside_flat(seg->b, flat));
}

int		point_inside_flat(t_point *point, t_flat *flat)
{
	return ((dist(point, flat->a) + dist(point, flat->b)
		+ dist(point, flat->c) + dist(point, flat->d))
		< (dist(flat->a, flat->b) + dist(flat->b, flat->c)
		+ dist(flat->c, flat->d) + dist(flat->d, flat->a)));
}

int		seg_crosses_flat(t_seg *seg, t_flat *flat)
{
	return ((point_inside_flat(seg->a, flat)
		&& !point_inside_flat(seg->b, flat))
		|| (!point_inside_flat(seg->a, flat)
		&& point_inside_flat(seg->b, flat)));
}

int		seg_below_flat(t_seg *seg, t_flat *flat)
{
	return (seg->a->z < flat->a->z
		&& seg->a->z < flat->b->z
		&& seg->a->z < flat->c->z
		&& seg->a->z < flat->d->z
		&& seg->b->z < flat->a->z
		&& seg->b->z < flat->b->z
		&& seg->b->z < flat->c->z
		&& seg->b->z < flat->d->z);
}

void	free_flats(t_flat **flats)
{
	t_flat	*flat_to_free;

	while (*flats)
	{
		flat_to_free = *flats;
		*flats = (*flats)->next;
		ft_memdel((void **)&flat_to_free->a);
		ft_memdel((void **)&flat_to_free->b);
		ft_memdel((void **)&flat_to_free->c);
		ft_memdel((void **)&flat_to_free->d);
		ft_memdel((void **)&flat_to_free);
	}
}

void	draw_segs(t_env *env, t_seg *segs)
{
	t_seg	*temp;

	temp = segs->next;
	while (temp != segs)
	{
		draw_seg(env, temp->a, temp->b);
		temp = temp->next;
	}
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

void	free_segs(t_seg **segs)
{
	t_seg	*temp;
	t_seg	*seg_to_free;

	temp = (*segs)->next;
	while (temp != *segs)
	{
		seg_to_free = temp;
		temp = temp->next;
		ft_memdel((void **)&seg_to_free->a);
		ft_memdel((void **)&seg_to_free->b);
		ft_memdel((void **)&seg_to_free);
	}
}
