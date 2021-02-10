/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hach <ael-hach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 16:07:32 by ael-hach          #+#    #+#             */
/*   Updated: 2021/02/09 16:10:13 by ael-hach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H
# include "mlx/mlx.h"
# include "parser/parser.h"
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <stdio.h>
# include <math.h>

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
# define MOVE_SPD 0.2
# define ROT_SPD .06

typedef struct		s_data
{
	void	*img;
	int		*addr;
	int		width;
	int		height;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}					t_data;

typedef struct		s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	move_speed;
	double	rot_speed;
	double	plane_x;
	double	plane_y;
}					t_player;

typedef struct		s_game
{
	void			*mlx;
	void			*win;
	t_data			win_buffer;
	t_player		player;
	t_colors		colors;
	t_resolution	res;
	t_data			textures[5];
	int				sprite_count;
	char			**world_map;
	bool			is_save;
	t_coordinate	sprite_positions[200];
}					t_game;

typedef struct		s_square
{
	int	x;
	int	y;
}					t_square;

typedef struct		s_wall_stripe
{
	int				x;
	double			dist;
	int				side;
	double			wall_x;
	int				height;
}					t_wall_stripe;

typedef struct		s_ray
{
	t_coordinate	dir;
	t_square		map_pos;
	t_coordinate	delta_dist;
	t_coordinate	side_dist;
	t_square		step_dir;
}					t_ray;

typedef struct		s_interval
{
	int	start;
	int	end;
}					t_interval;

typedef struct		s_tex_stripe {
	int		x;
	int		y;
	double	pos;
	double	step;
}					t_tex_stripe;

typedef struct		s_pair
{
	double	first;
	int		second;
}					t_pair;

typedef struct		s_sprite
{
	double			x;
	double			y;
	t_coordinate	trans;
	int				screen_x;
	t_resolution	res;
	t_square		draw_start;
	t_square		draw_end;
}					t_sprite;

typedef struct		s_screenshot
{
	int				width_bytes;
	int				padding_size;
	int				stride;
	unsigned char	*file_header;
	unsigned char	*info_header;
}					t_screenshot;
int					g_player_count;
typedef struct		s_bitmapheader{
	uint32_t	file_size;
	uint32_t	off_bits;
	uint32_t	size;
	uint32_t	info_size;
	int32_t		width;
	int32_t		height;
	uint16_t	planes;
	uint16_t	bit_count;
	uint32_t	image_size;
	int			width_in_bytes;
	int			fd;
}					t_bitmapheader;

t_game				create_game(int argc, char **argv);
void				exit_game(t_game *game, int status);
int					on_key_press(int keycode, t_game *game);
int					on_red_cross_press(t_game *game);
int					draw(t_game *game);
void				my_mlx_pixel_put(t_game *game, int x, int y, int color);
void				draw_vertical_line(t_game *game, int x, t_interval range,
					int color);
t_ray				get_ray(t_player player, int win_width, int x);
t_wall_stripe		cast_ray(t_player *player,
t_resolution res, int x, char **world_map);
void				draw_walls(t_game *game, double z_buffer[]);
t_sprite			get_sprite(t_game *game, int sprite_order[], int i);
void				sort_sprites(int *order, double *dist, int amount);
void				draw_every_sprite(t_game *game, double z_buffer[], int num);
t_player			create_player(double x, double y, char dir);
void				move_up(t_player *player, char **world_map);
void				move_down(t_player *player, char **world_map);
void				move_right(t_player *player, char **world_map);
void				move_left(t_player *player, char **world_map);
void				turn_right(t_player *player);
void				turn_left(t_player *player);
void				take_screenshot(t_game game);
#endif
