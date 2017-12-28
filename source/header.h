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

#ifndef HEADER_H
# define HEADER_H

# include "../minilibx_macos/mlx.h"
# include "../libft/libft.h"
# include <math.h>
# include <stdio.h>

# define BASIC_COLOR 0xFFFFFF
# define WHITE 0xAAAAAA
# define BLACK 0x000000
# define GREEN 0x008000
# define RED 0xFF0000
# define LIME 0x00FF00
# define BLUE 0x0000FF
# define YELLOW 0xFFFF00
# define COLOR_OF_ONES 0xFFFFFF
# define TEST 0xAABBCC

# define ESC 53
# define W 13
# define A 0
# define S 1
# define D 2
# define Q 12
# define E 14
# define ARROW_UP 126
# define ARROW_DOWN 125
# define ARROW_LEFT 123
# define ARROW_RIGHT 124

typedef struct	s_z_buff_elem
{
	double		z;
	int			color;
}				t_z_buff_elem;

typedef struct	s_point
{
	double			x;
	double			y;
	double			z;
	int				color;
}				t_point;

typedef struct	s_point_row
{
	t_point				**points;
	struct s_point_row	*next;
}				t_point_row;

typedef struct	s_env {
	void			*mlx;
	void			*window;
	double			wwidth;
	double			wheight;
	t_point_row		*pointset;
	int				fwidth;
	int				fheight;
	int				ang_x;
	int				ang_y;
	int				ang_z;
	int				shift_x;
	int				shift_y;
	double			seglen;
	t_z_buff_elem	**z_buff;
	int				serf;
}				t_env;

t_point			*get_point(double x, double y, double z, int color);

void			set_figure(int fd, t_env *env);

void			add_point_row(t_point_row **point_row, t_point **points);

void			draw(t_env *env);

t_point			get_modified_point(t_env *env, t_point *point);

int				is_point_in_pointset(t_point *point, t_point **pointset);

void			move_point(t_point *point, double x_shift, double y_shift);

double			degree_to_rad(int degree);

unsigned int	get_color(char *s);

int				show_invalid_color_error(void);

int				show_invalid_size_error(void);

int				show_invalid_file_error(void);

int				show_malloc_error(void);

void			sort(t_point *array);

void			clear_z_buffer(t_env *env);

// funcs to delete

void			print_point(t_point *point);

void			print_point_row(t_point_row *point_row);

void			draw_axis(t_env *env, int color);

void			print_cross(t_point **points);

#endif
