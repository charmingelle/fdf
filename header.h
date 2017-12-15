#include "minilibx_macos/mlx.h"
#include "get_next_line.h"
#include "libft/libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#define WHITE 0xAAAAAA
#define GREEN 0x008000
#define RED 0xFF0000
#define LIME 0x00FF00
#define BLUE 0x0000FF
#define YELLOW 0xFFFF00
#define DEGREE45 0.785398
#define DEGREE5 0.0872665
#define DEGREE90 1.5708
#define DEGREE225 3.92699
#define DEGREE180 3.14159

#define Rx 3.92699
#define Ry 0
#define Rz 1.5708

#define RAD1 1
#define ESC 53
#define W 13
#define A 0
#define S 1
#define D 2
#define Q 12
#define E 14
#define SEGMENT_LEN 50

typedef struct	s_point
{
	double x;
	double y;
	double z;
}				t_point;

typedef struct	s_point_row
{
	t_point				**points;
	struct s_point_row	*next;
}				t_point_row;

typedef struct	s_flat
{
	t_point			*a;
	t_point			*b;
	t_point			*c;
	t_point			*d;
	struct s_flat	*next;
}				t_flat;

typedef struct	s_segment
{
	t_point				*a;
	t_point				*b;
	struct s_segment	*next;
	struct s_segment	*prev;
}				t_segment;

typedef struct  s_env {
    void            *mlx;
    void            *window;
    double          width;
    double          height;
    t_point_row     *point_set;
    int             figure_width;
    int             figure_height;
    int             figure_depth;
    double          angle_x;
    double          angle_y;
    double          angle_z;
    int             color;
}               t_env;

t_point 		*create_point(double x, double y, double z);

int				handle_key_press(int keycode, t_env *env);

void			rotate_point_x(t_point **point, double angle);

void			rotate_point_y(t_point **point, double angle);

void			rotate_point_z(t_point **point, double angle);

void			draw_axis(t_env *env, int color);

void			draw_segment(t_env *env, t_point *p1, t_point *p2);

t_point			**get_points_from_z_coords(char **z_coords, int row_number, int *width);

void			free_z_coords(char **z_coords);

t_point_row		*create_point_set(int fd, int *width, int *height);

t_point_row		*create_point_row(t_point **points);

void			add_point_row(t_point_row **point_row, t_point **points);

void			ft_swap(t_point **a, t_point **b);

void			draw(t_env *env);

// t_point			**get_rotated_point(t_env *env, t_point *point);

t_point			*get_rotated_point(t_env *env, t_point *point);

t_point			*get_segments_cross(t_point *a_start, t_point *a_end, t_point *b_start, t_point *b_end);

t_point			**get_segment_flat_cross(t_segment *segment, t_flat *flat);

int				equal_points(t_point *a, t_point *b);

int				is_point_in_pointset(t_point *point, t_point **pointset);

void    		get_rotated_segments_and_flats(t_env *env);

int				point_above_straight(t_point *point, t_point *a, t_point *b);

int				segment_above_straight(t_segment *segment, t_point *a, t_point *b);

int				point_below_straight(t_point *point, t_point *a, t_point *b);

int				segment_below_straight(t_segment *segment, t_point *a, t_point *b);

int         	segment_inside_flat(t_segment *segment, t_flat *flat);

int				segment_below_flat(t_segment *segment, t_flat *flat);

void			remove_invisible_segments(t_segment **segment, t_flat **flat);

void			process_segment(t_segment **segments, t_segment *segment, t_flat **flats);

t_flat  		*create_flat(t_point *a, t_point *b, t_point *c, t_point *d);

void    		add_flat(t_flat **flats, t_flat *new);

t_segment		*create_segment(t_point *a, t_point *b);

void    		add_segment(t_segment **segments, t_segment *new);

void			add_segment_back(t_segment **segments, t_segment *new);

void			delete_segment(t_segment *to_delete);

double			get_z_index(t_point *start, t_point *end, double x, double y);

int				flat_contains_segment(t_segment *segment, t_flat *flat);

// funcs to delete

void			print_point(t_point *point);

void			print_point_row(t_point_row *point_row);

void			print_segment(t_segment *segment);

void			print_segments(t_segment **segments);

void			print_flat(t_flat *flat);

void			print_flats(t_flat **flats);

///
