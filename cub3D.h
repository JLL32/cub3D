#ifndef CUB3D_H
# define CUB3D_H
#include "mlx/mlx.h"
#include "parser/parser.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>

# define TEX_WIDTH 64
# define TEX_HEIGHT 64
# define SP_TEX 4
# define KEY_UP 126
# define KEY_DOWN 125
# define KEY_RIGHT 124
# define KEY_LEFT 123
# define KEY_A 0
# define KEY_S 1
# define KEY_W 13
# define KEY_D 2
# define KEY_ESC 53
# define PLANE .66
# define MOVE_SPD 0.3
# define ROT_SPD .06

typedef struct s_data
{
	void *img;
	int *addr;
	int width;
	int height;
	int bits_per_pixel;
	int line_length;
	int endian;
} t_data;

typedef struct s_player {
	double pos_x;
	double pos_y;
	double dir_x;
	double dir_y;
	double move_speed;
	double rot_speed;
	double plane_x;
	double plane_y;
} t_player;

// typedef struct s_resolution {
// 	int height;
// 	int width;
// } t_resolution;

// typedef struct s_colors {
// 	int floor;
// 	int ceiling;
// } t_colors;

typedef struct s_game
{
	void *mlx;
	void *win;
	t_data win_buffer;
	t_player player;
	t_colors colors;
	t_resolution res;
	t_data textures[5];
	int sprite_count;
	char **world_map;
	bool is_save;
	t_coordinate sprite_positions[200];
} t_game;

// typedef struct s_coordinate {
// 	double x;
// 	double y;
// } t_coordinate;

typedef struct s_square {
	int x;
	int y;
} t_square;

typedef struct s_wall_stripe
{
	double dist;
	int side;
	double wall_x;
	int height;
} t_wall_stripe;

typedef struct s_ray {
	t_coordinate dir;
	t_square map_pos;
	t_coordinate delta_dist;
	t_coordinate side_dist;
	t_square step_dir;
} t_ray;

typedef struct s_interval {
	int start;
	int end;
} t_interval;

typedef struct s_tex_stripe {
	int x;
	int y;
	double pos;
	double step;
} t_tex_stripe;

typedef struct s_sprite
{
	double x;
	double y;
	t_coordinate trans;
	int screen_x;
	t_resolution res;
	t_square draw_start;
	t_square draw_end;
} t_sprite;
/* t_wall_stripe detect_wall(t_player *player, t_coordinate side_dist, */
/* 		t_coordinate delta_dist, t_coordinate ray_dir, t_square map, */
/* 		t_resolution res, t_square step_dir); */

t_player create_player(double x, double y, char dir);
void move_up(t_player *player, char **world_map);
void move_down(t_player *player, char **world_map);
void move_right(t_player *player, char **world_map);
void move_left(t_player *player, char **world_map);
void turn_right(t_player *player);
void turn_left(t_player *player);
#endif
