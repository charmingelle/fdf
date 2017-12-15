#include "header.h"

void	draw_axis(t_env *env, int color)
{
	for (double x = (env->width - env->height) / 2; x < env->width - (env->width - env->height) / 2; x++)
		mlx_pixel_put(env->mlx, env->window, x, (-1) * x + (env->width + env->height) / 2, color);
	for (double x = 0; x < env->width; x++)
		mlx_pixel_put(env->mlx, env->window, x, env->height / 2, color);
	for (double y = 0; y < env->height; y++)
		mlx_pixel_put(env->mlx, env->window, env->width / 2, y, color);
}

void	get_rotated_segments_and_flats(t_env *env)
{
	t_point_row	*pointset;
	t_segment	*segments;
	t_flat		*flats;
	int			i;
	t_segment	*segment_to_free;
	t_flat		*flat_to_free;
	t_segment	*tmp;

	pointset = env->point_set;
	segments = create_segment(NULL, NULL);
	flats = NULL;
	while (pointset->next)
	{
		add_segment(&segments, create_segment(get_rotated_point(env, pointset->next->points[0]), get_rotated_point(env, pointset->points[0])));
		i = 0;
		while (pointset->points[++i])
		{
			add_segment(&segments, create_segment(get_rotated_point(env, pointset->points[i - 1]), get_rotated_point(env, pointset->points[i])));
			add_segment(&segments, create_segment(get_rotated_point(env, pointset->next->points[i]), get_rotated_point(env, pointset->points[i])));
			add_flat(&flats, create_flat(get_rotated_point(env, pointset->points[i - 1]),
									get_rotated_point(env, pointset->points[i]),
									get_rotated_point(env, pointset->next->points[i]),
									get_rotated_point(env, pointset->next->points[i - 1])));
		}
		pointset = pointset->next;
	}
	i = 0;
	while (pointset->points[++i])
		add_segment(&segments, create_segment(get_rotated_point(env, pointset->points[i - 1]), get_rotated_point(env, pointset->points[i])));
	// print_flats(&flats);
	remove_invisible_segments(&segments, &flats);
	while (flats)
	{
		flat_to_free = flats;
		flats = flats->next;
		ft_memdel((void **)&flat_to_free->a);
		ft_memdel((void **)&flat_to_free->b);
		ft_memdel((void **)&flat_to_free->c);
		ft_memdel((void **)&flat_to_free->d);
		ft_memdel((void **)&flat_to_free);
	}	
	tmp = segments->next;
	while (tmp != segments)
	{
		draw_segment(env, tmp->a, tmp->b);
		segment_to_free = tmp;
		tmp = tmp->next;
		ft_memdel((void **)&segment_to_free->a);
		ft_memdel((void **)&segment_to_free->b);
		ft_memdel((void **)&segment_to_free);
	}
}

// int		point_above_straight(t_point *point, t_point *a, t_point *b)
// {
// 	return (((b->y - a->y) * point->x + (a->x - b->x) * point->y + b->x * a->y - b->y * a->x) <= 0);
// }

int		segment_above_straight(t_segment *segment, t_point *a, t_point *b)
{
	return (
		(((b->y - a->y) * segment->a->x + (a->x - b->x) * segment->a->y + b->x * a->y - b->y * a->x) <= 0)
		&& (((b->y - a->y) * segment->b->x + (a->x - b->x) * segment->b->y + b->x * a->y - b->y * a->x) <= 0)
	);
	// return (point_above_straight(segment->a, a, b) && point_above_straight(segment->b, a, b));
}

// int		point_below_straight(t_point *point, t_point *a, t_point *b)
// {
// 	return (((b->y - a->y) * point->x + (a->x - b->x) * point->y + b->x * a->y - b->y * a->x) >= 0);
// }

int		segment_below_straight(t_segment *segment, t_point *a, t_point *b)
{
	return (
		(((b->y - a->y) * segment->a->x + (a->x - b->x) * segment->a->y + b->x * a->y - b->y * a->x) <= 0)
		&& (((b->y - a->y) * segment->b->x + (a->x - b->x) * segment->b->y + b->x * a->y - b->y * a->x) <= 0)
	);
	// return (point_below_straight(segment->a, a, b) && point_below_straight(segment->b, a, b));
}

int		flat_contains_segment(t_segment *segment, t_flat *flat)
{
	return ((equal_points(segment->a, flat->a) && equal_points(segment->b, flat->b))
		|| (equal_points(segment->a, flat->b) && equal_points(segment->b, flat->c))
		|| (equal_points(segment->a, flat->c) && equal_points(segment->b, flat->d))
		|| (equal_points(segment->a, flat->d) && equal_points(segment->b, flat->a)));
}

int		segment_inside_flat(t_segment *segment, t_flat *flat)
{
	return ((segment_above_straight(segment, flat->a, flat->b)
		&& segment_above_straight(segment, flat->b, flat->c)
		&& segment_below_straight(segment, flat->c, flat->d)
		&& segment_below_straight(segment, flat->d, flat->a))
		|| (segment_above_straight(segment, flat->a, flat->b)
		&& segment_below_straight(segment, flat->b, flat->c)
		&& segment_below_straight(segment, flat->c, flat->d)
		&& segment_above_straight(segment, flat->d, flat->a))
		|| (segment_below_straight(segment, flat->a, flat->b)
		&& segment_above_straight(segment, flat->b, flat->c)
		&& segment_above_straight(segment, flat->c, flat->d)
		&& segment_below_straight(segment, flat->d, flat->a))
		|| (segment_below_straight(segment, flat->a, flat->b)
		&& segment_below_straight(segment, flat->b, flat->c)
		&& segment_above_straight(segment, flat->c, flat->d)
		&& segment_above_straight(segment, flat->d, flat->a)));
}

int		segment_below_flat(t_segment *segment, t_flat *flat)
{
	return (segment->a->z < flat->a->z
		&& segment->a->z < flat->b->z
		&& segment->a->z < flat->c->z
		&& segment->a->z < flat->d->z
		&& segment->b->z < flat->a->z
		&& segment->b->z < flat->b->z
		&& segment->b->z < flat->c->z
		&& segment->b->z < flat->d->z);
}

void	remove_invisible_segments(t_segment **segments, t_flat **flats)
{
	t_segment	*tmp;

	tmp = *segments;
	while ((tmp = tmp->next) != *segments)
		process_segment(segments, tmp, flats);
}

void	process_segment(t_segment **segments, t_segment *segment, t_flat **flats)
{
	t_point		**cross;

	while (*flats)
	{
		if (!flat_contains_segment(segment, *flats))
		{
			cross = get_segment_flat_cross(segment, *flats);
			if (segment_inside_flat(segment, *flats) && segment_below_flat(segment, *flats))
			{
				delete_segment(segment);
				return ;
			}
			else if (cross && cross[0] && !cross[1])
			{
				add_segment_back(segments, create_segment(segment->a, cross[0]));
				add_segment_back(segments, create_segment(cross[0], segment->b));
				return ;
			}
			else if (cross && cross[0] && cross[1])
			{
				add_segment_back(segments, create_segment(segment->a, cross[0]));
				add_segment_back(segments, create_segment(cross[0], cross[1]));
				add_segment_back(segments, create_segment(cross[1], segment->b));
				return ;
			}
		}
		flats = &((*flats)->next);
	}
}

void	draw_segment(t_env *env, t_point *p1, t_point *p2)
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
