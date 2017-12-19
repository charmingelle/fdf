#include "header.h"

void	print_point(t_point *point)
{
	printf("(%g, %g, %g)\n", point->x, point->y, point->z);
}

void	print_point_row(t_point_row *point_row)
{
	int i;

	i = 0;
	while ((point_row->points)[i] != NULL)
	{
		print_point((point_row->points)[i]);
		i++;
	}
	printf("\n");
}

void	print_seg(t_seg *seg)
{
	printf("s(%g %g)-(%g %g)\n", seg->a->x, seg->a->y, seg->b->x, seg->b->y);
}

void	print_segs(t_seg **segs)
{
	t_seg	*tmp;
	tmp = *segs;
	while ((tmp = tmp->next) != *segs)
		print_seg(tmp);
}

void	print_flat(t_flat *flat)
{
	printf("f(%g %g)-(%g %g)-(%g %g)-(%g %g)\n",
			flat->a->x, flat->a->y,
			flat->b->x, flat->b->y,
			flat->c->x, flat->c->y,
			flat->d->x, flat->d->y);
}

void	print_flats(t_flat **flats)
{
	while (*flats)
	{
		print_flat(*flats);
		flats = &((*flats)->next);
	}
}

void	draw_axis(t_env *env, int color)
{
	for (double x = (env->w_width - env->w_height) / 2; x < env->w_width - (env->w_width - env->w_height) / 2; x++)
		mlx_pixel_put(env->mlx, env->window, x, (-1) * x + (env->w_width + env->w_height) / 2, color);
	for (double x = 0; x < env->w_width; x++)
		mlx_pixel_put(env->mlx, env->window, x, env->w_height / 2, color);
	for (double y = 0; y < env->w_height; y++)
		mlx_pixel_put(env->mlx, env->window, env->w_width / 2, y, color);
}

void	print_cross(t_point **points)
{
	int i;

	i = -1;
	while (points[++i])
		print_point(points[i]);
}
