#include "minilibx_macos/mlx.h"
#include "get_next_line.h"
#include "libft/libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#define WHITE 0xAAAAAA
#define RED 0xFF0000
#define LIME 0x00FF00
#define BLUE 0x0000FF
#define YELLOW 0xFFFF00
#define DEGREE45 0.785398
#define DEGREE5 0.0872665
#define RAD1 1
#define ESC 53
#define W 13
#define A 0
#define S 1
#define D 2
#define Q 12
#define E 14

typedef struct	s_point
{
	int x;
	int y;
	int z;
}				t_point;

typedef struct	s_point_line
{
	struct s_point_line	*prev;
	t_point				**points;
	struct s_point_line	*next;
}				t_point_line;

typedef struct	s_env {
	void			*mlx;
	void			*window;
	int				width;
	int				height;
	t_point_line	*point_set;
	int				color;
}				t_env;

t_point 		*create_point(int x, int y, int z);

int				square_function(int x);

int				handle_key_press(int keycode, t_env *env);

void			rotate_point_x(t_point **point, int direction);

void			rotate_point_y(t_point **point, int direction);

void			rotate_point_z(t_point **point, int direction);

void			rotate_point_set(t_env *env, void(*f)(t_point **, int), int direction);

void			rotate_point_x(t_point **point, int direction);

void			rotate_point_y(t_point **point, int direction);

void			rotate_point_z(t_point **point, int direction);

void			rotate_point_set(t_env *env, void(*f)(t_point **, int), int direction);

int				get_2d_x(t_env *env, t_point *point);

int				get_2d_y(t_env *env, t_point *point);

void			draw_point(t_env *env, t_point *point, int color);

void			draw_axis(t_env *env, int color);

void			draw_segment(t_env *env, t_point *p1, t_point *p2, int color);

void			draw_graph(t_env *env, int(*f)(int), int start, int end, int color);

void			draw_point_set(t_env *env);

void			erase_point_set(t_env *env);

void			draw_rotated(t_env *env, void(*f)(t_point **, int), int direction);

int				count_lines(int fd);

t_point			**get_points_from_z_coords(char **z_coords, int line_number);

void			free_z_coords(char **z_coords);

t_point_line	*create_point_set(int fd);

t_point_line	*create_point_line(t_point **points);

void			add_point_line(t_point_line **point_line, t_point **points);
