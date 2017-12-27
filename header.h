#include "minilibx_macos/mlx.h"
#include "libft/libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#define WHITE 0xAAAAAA
#define BASIC_COLOR 0xAAAAAA
#define BLACK 0x000000
#define GREEN 0x008000
#define RED 0xFF0000
#define LIME 0x00FF00
#define BLUE 0x0000FF
#define YELLOW 0xFFFF00
#define COLOR_OF_ONES 0xFFFFFF

#define ESC 53
#define W 13
#define A 0
#define S 1
#define D 2
#define Q 12
#define E 14

typedef struct	s_z_buff_elem
{
	double			z;
	unsigned int	color;
}				t_z_buff_elem;

typedef struct	s_point
{
	double			x;
	double			y;
	double			z;
    int             color;
}				t_point;

typedef struct	s_point_row
{
	t_point				**points;
	struct s_point_row	*next;
}				t_point_row;

typedef struct  s_env {
    void            *mlx;
    void            *window;
    double          w_width;
    double          w_height;
    t_point_row     *pointset;
    int             f_width;
    int             f_height;
    int				angle_x;
    int				angle_y;
    int				angle_z;
    double			seglen;
    t_z_buff_elem	**z_buff;
}               t_env;

t_point 		*get_point(double x, double y, double z, int color);

int				handle_key_press(int keycode, t_env *env);

t_point			**get_points_from_z_coords(t_env *env, char **z_coords,
    int row_number);

void			free_z_coords(char **z_coords);

void			set_figure(int fd, t_env *env);

void			add_point_row(t_point_row **point_row, t_point **points);

void			draw(t_env *env);

t_point			get_modified_point(t_env *env, t_point *point);

int				equal_points(t_point *a, t_point *b);

int				is_point_in_pointset(t_point *point, t_point **pointset);

double			get_z_index(t_point *start, t_point *end, double x, double y);

t_env			get_env(int fd);

void			move_point(t_point *point, double x_shift, double y_shift);

void			center_figure(t_env *env);

int				mouse_handle(int key, int x, int y, t_env *env);

void            ft_swap(void **a, void **b);

void			draw_triangle(t_env *env, t_point *a, t_point *b, t_point *c);

void			draw_top_middle_half_triangle(t_env *env, t_point *top,
    t_point *middle, t_point *bottom);

void			draw_middle_bottom_half_triangle(t_env *env, t_point *top,
    t_point *middle, t_point *bottom);

void			draw_segs_and_triags(t_env *env);

void			draw_seg(t_env *env, t_point *p1, t_point *p2);

int             count_x_on_seg(t_env *env, t_point *start, t_point *end, double y);

t_z_buff_elem   **init_z_buff(t_env env);

double          degree_to_rad(int degree);

unsigned int	ft_atoi_hex_color(char *s);

// funcs to delete

void			print_point(t_point *point);

void			print_point_row(t_point_row *point_row);

void			draw_axis(t_env *env, int color);

void			print_cross(t_point **points);

///
