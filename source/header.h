/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/29 14:43:20 by grevenko          #+#    #+#             */
/*   Updated: 2017/12/29 14:46:30 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include "../minilibx_macos/mlx.h"
# include "../libft/libft.h"
# include <math.h>

# define BASIC_COLOR 0xFFFFFF

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

int				mouse_handle(int key, int x, int y, t_env *env);

int				handle_key_press(int keycode, t_env *env);

int				get_mid_color(int start, int end, double to_pass,
double passed);

void			draw_segs_and_triags(t_env *env);

#endif
