#include "header.h"

// void	draw_axis(t_env *env, int color)
// {
// 	for (double x = (env->width - env->height) / 2; x < env->width - (env->width - env->height) / 2; x++)
// 		mlx_pixel_put(env->mlx, env->window, x, (-1) * x + (env->width + env->height) / 2, color);
// 	for (double x = 0; x < env->width; x++)
// 		mlx_pixel_put(env->mlx, env->window, x, env->height / 2, color);
// 	for (double y = 0; y < env->height; y++)
// 		mlx_pixel_put(env->mlx, env->window, env->width / 2, y, color);
// }

void	draw(t_env *env)
{
	t_seg		*segs;
	t_flat		*flats;

	mlx_clear_window(env->mlx, env->window);
	fill_segs_amd_flats(env, &segs, &flats);
	remove_invisible_segs(&segs, &flats);
	free_flats(&flats);
	draw_segs(env, segs);
	free_segs(&segs);
}

void	fill_segs_amd_flats(t_env *env, t_seg **segs, t_flat **flats)
{
	t_point_row	*ps;
	int			i;

	*segs = get_seg(NULL, NULL);
	*flats = NULL;
	ps = env->point_set;
	while (ps)
	{
		i = -1;
		while (ps->points[++i])
		{
			if (i >= 1)
				add_seg(segs, get_seg(get_rot_point(env, ps->points[i - 1]),
					get_rot_point(env, ps->points[i])));
			if (ps->next)
				add_seg(segs, get_seg(get_rot_point(env, ps->next->points[i]),
					get_rot_point(env, ps->points[i])));
			if (i >= 1 && ps->next)
				add_flat(flats, get_flat(get_rot_point(env, ps->points[i - 1]),
					get_rot_point(env, ps->points[i]), get_rot_point(env, ps->next->points[i]),
					get_rot_point(env, ps->next->points[i - 1])));
		}
		ps = ps->next;
	}
}

void	remove_invisible_segs(t_seg **segs, t_flat **flats)
{
	t_seg	*temp;

	temp = *segs;
	while ((temp = temp->next) != *segs)
		process_seg(segs, temp, flats);
}

void	process_seg(t_seg **segs, t_seg *seg, t_flat **flats)
{
	t_point		**cross;

	while (*flats)
	{
		if (!flat_contains_seg(seg, *flats))
		{
			cross = get_seg_flat_cross(seg, *flats);
			if (seg_inside_flat(seg, *flats) && seg_below_flat(seg, *flats))
			{
				delete_seg(seg);
				return ;
			}
			// if (cross && cross[0] && !cross[1])
			// {
			// 	add_seg_back(segs, get_seg(seg->a, cross[0]));
			// 	add_seg_back(segs, get_seg(cross[0], seg->b));
			// 	return ;
			// }
			// if (cross && cross[0] && cross[1])
			// {
			// 	add_seg_back(segs, get_seg(seg->a, cross[0]));
			// 	add_seg_back(segs, get_seg(cross[0], cross[1]));
			// 	add_seg_back(segs, get_seg(cross[1], seg->b));
			// 	return ;
			// }
		}
		flats = &((*flats)->next);
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

int		seg_above_straight(t_seg *seg, t_point *a, t_point *b)
{
	return (
		(((b->y - a->y) * seg->a->x + (a->x - b->x) * seg->a->y + b->x * a->y - b->y * a->x) <= 0)
		&& (((b->y - a->y) * seg->b->x + (a->x - b->x) * seg->b->y + b->x * a->y - b->y * a->x) <= 0)
	);
}

int		seg_below_straight(t_seg *seg, t_point *a, t_point *b)
{
	return (
		(((b->y - a->y) * seg->a->x + (a->x - b->x) * seg->a->y + b->x * a->y - b->y * a->x) <= 0)
		&& (((b->y - a->y) * seg->b->x + (a->x - b->x) * seg->b->y + b->x * a->y - b->y * a->x) <= 0)
	);
}

int		flat_contains_seg(t_seg *seg, t_flat *flat)
{
	return ((equal_points(seg->a, flat->a) && equal_points(seg->b, flat->b))
		|| (equal_points(seg->a, flat->b) && equal_points(seg->b, flat->c))
		|| (equal_points(seg->a, flat->c) && equal_points(seg->b, flat->d))
		|| (equal_points(seg->a, flat->d) && equal_points(seg->b, flat->a)));
}

int		seg_inside_flat(t_seg *seg, t_flat *flat)
{
	return ((seg_above_straight(seg, flat->a, flat->b)
		&& seg_above_straight(seg, flat->b, flat->c)
		&& seg_below_straight(seg, flat->c, flat->d)
		&& seg_below_straight(seg, flat->d, flat->a))
		|| (seg_above_straight(seg, flat->a, flat->b)
		&& seg_below_straight(seg, flat->b, flat->c)
		&& seg_below_straight(seg, flat->c, flat->d)
		&& seg_above_straight(seg, flat->d, flat->a))
		|| (seg_below_straight(seg, flat->a, flat->b)
		&& seg_above_straight(seg, flat->b, flat->c)
		&& seg_above_straight(seg, flat->c, flat->d)
		&& seg_below_straight(seg, flat->d, flat->a))
		|| (seg_below_straight(seg, flat->a, flat->b)
		&& seg_below_straight(seg, flat->b, flat->c)
		&& seg_above_straight(seg, flat->c, flat->d)
		&& seg_above_straight(seg, flat->d, flat->a)));
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


void	draw_seg(t_env *env, t_point *p1, t_point *p2)
{
	double 	x1;
	double 	y1;
	double 	x2;
	double 	y2;
	double	t;
	int		color;

	if (p1->z > p2->z)
		ft_swap(&p1, &p2);
	x1 = p1->x + env->width / 2;
	y1 = -p1->y + env->height / 2;
	x2 = p2->x + env->width / 2;
	y2 = -p2->y + env->height / 2;
	color = env->color;
	t = -1.00;
	while (t <= 0)
	{
		mlx_pixel_put(env->mlx, env->window, (x1 - x2) * t + x1, (y1 - y2) * t + y1, color);
		t += 0.001;
	}
}
