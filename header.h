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

typedef struct	s_seg
{
	t_point				*a;
	t_point				*b;
	struct s_seg	*next;
	struct s_seg	*prev;
}				t_seg;

typedef struct  s_env {
    void            *mlx;
    void            *window;
    double          w_width;
    double          w_height;
    t_point_row     *pointset;
    int             f_width;
    int             f_height;
    double          angle_x;
    double          angle_y;
    double          angle_z;
    int             color;
    double			seglen;
}               t_env;

t_point 		*get_point(double x, double y, double z);

int				handle_key_press(int keycode, t_env *env);

void			rotate_point_x(t_point **point, double angle);

void			rotate_point_y(t_point **point, double angle);

void			rotate_point_z(t_point **point, double angle);

void			draw_seg(t_env *env, t_point *p1, t_point *p2);

t_point			**get_points_from_z_coords(t_env *env, char **z_coords, int row_number);

void			free_z_coords(char **z_coords);

void			set_figure(int fd, t_env *env);

t_point_row		*get_point_row(t_point **points);

void			add_point_row(t_point_row **point_row, t_point **points);

void			ft_swap(t_point **a, t_point **b);

void			draw(t_env *env);

t_point			*get_rot_and_exp_point(t_env *env, t_point *point);

t_point			*get_segs_cross(t_point *a_start, t_point *a_end, t_point *b_start, t_point *b_end);

t_point			**get_seg_flat_cross(t_seg *seg, t_flat *flat);

int				equal_points(t_point *a, t_point *b);

int				is_point_in_pointset(t_point *point, t_point **pointset);

void    		get_rotated_segs_and_flats(t_env *env);

int				point_above_straight(t_point *point, t_point *a, t_point *b);

int				seg_above_straight(t_seg *seg, t_point *a, t_point *b);

int				point_below_straight(t_point *point, t_point *a, t_point *b);

int				seg_below_straight(t_seg *seg, t_point *a, t_point *b);

int         	seg_inside_flat(t_seg *seg, t_flat *flat);

int				seg_below_flat(t_seg *seg, t_flat *flat);

void			remove_invisible_segs(t_seg **seg, t_flat **flat);

void			process_seg(t_seg **segs, t_seg *seg, t_flat **flats);

t_flat  		*get_flat(t_point *a, t_point *b, t_point *c, t_point *d);

void    		add_flat(t_flat **flats, t_flat *new);

t_seg			*get_seg(t_point *a, t_point *b);

void    		add_seg(t_seg **segs, t_seg *new);

void			add_seg_back(t_seg **segs, t_seg *new);

void			delete_seg(t_seg *to_delete);

double			get_z_index(t_point *start, t_point *end, double x, double y);

int				flat_contains_seg(t_seg *seg, t_flat *flat);

void			draw_segs(t_env *env, t_seg *segs);

void			free_flats(t_flat **flats);

void			free_segs(t_seg **segs);

void			get_rotated_segs(t_env *env);

void			fill_segs_amd_flats(t_env *env, t_seg **segs, t_flat **flats);

t_env			*get_env(int fd);

int				handle_key_press(int keycode, t_env *env);

void			move_point(t_point *point, double x_shift, double y_shift);

void			center_figure(t_env *env);

int				mouse_handle(int key, int x, int y, t_env *env);

double			dist(t_point *a, t_point *b);

int				point_inside_flat(t_point *point, t_flat *flat);

int				seg_inside_flat(t_seg *seg, t_flat *flat);

int				seg_crosses_flat(t_seg *seg, t_flat *flat);

int				flat_contains_seg(t_seg *seg, t_flat *flat);

int				seg_inside_flat_side(t_seg *seg, t_point *side_start, t_point *side_end);

// funcs to delete

void			print_point(t_point *point);

void			print_point_row(t_point_row *point_row);

void			print_seg(t_seg *seg);

void			print_segs(t_seg **segs);

void			print_flat(t_flat *flat);

void			print_flats(t_flat **flats);

void			draw_axis(t_env *env, int color);

void			print_cross(t_point **points);

///
