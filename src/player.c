#include "../cub3D.h"

/* typedef struct s_player { */
/* 	double pos_x; */
/* 	double pos_y; */
/* 	double dir_x; */
/* 	double dir_y; */
/* 	double move_speed; */
/* 	double rot_speed; */
/* 	double plane_x; */
/* 	double plane_y; */
/* } t_player; */

/* t_player create_player(); */
/* void move_up(t_player *player); */
/* void move_down(t_player *player); */
/* void move_right(t_player *player); */
/* void move_left(t_player *player); */
/* void turn_right(t_player *player); */
/* void turn_left(t_player *player); */

t_player create_player(double x, double y, char dir)
{
	// TODO: position coordinates need to be initiated from the parser
	t_player player;
	player.pos_x = x;
	player.pos_y = y;
	player.dir_x = -1.0;
	player.dir_y = 0.0;
	player.move_speed = 0.5;
	player.rot_speed = 0.06;
	player.plane_x = 0;
	player.plane_y = .66;
	return player;
}

void move_up(t_player *player, char **world_map)
{
	double next_x;
	double next_y;
	
	next_x = player->pos_x + player->dir_x * player->move_speed;
	next_y = player->pos_y + player->dir_y * player->move_speed;
	if (world_map[(int)(next_x)][(int)(player->pos_y)] == '0')
		player->pos_x = next_x;
	if (world_map[(int)(player->pos_x)][(int)(next_y)] == '0')
		player->pos_y = next_y;
}

void move_down(t_player *player, char **world_map)
{
	double next_x;
	double next_y;
	
	next_x = player->pos_x - player->dir_x * player->move_speed;
	next_y = player->pos_y - player->dir_y * player->move_speed;
	if (world_map[(int)(next_x)][(int)(player->pos_y)] == '0')
		player->pos_x = next_x;
	if (world_map[(int)player->pos_x][(int)(next_y)] == '0')
		player->pos_y = next_y;
}

void move_right(t_player *player, char **world_map)
{
	double next_x;
	double next_y;
	
	next_x = player->pos_x + player->plane_x * player->move_speed;
	next_y = player->pos_y + player->plane_y * player->move_speed;
	if (world_map[(int)(next_x)][(int)(player->pos_y)] == '0')
		player->pos_x = next_x;
	if (world_map[(int)(player->pos_x)][(int)(next_y)] == '0')
		player->pos_y = next_y;
}

void move_left(t_player *player, char **world_map)
{
	double next_x;
	double next_y;
	
	next_x = player->pos_x - player->plane_x * player->move_speed;
	next_y = player->pos_y - player->plane_y * player->move_speed;
	if (world_map[(int)(next_x)][(int)(player->pos_y)] == '0')
		player->pos_x = next_x;
	if (world_map[(int)player->pos_x][(int)(next_y)] == '0')
		player->pos_y = next_y;
}

void turn_right(t_player *player)
{
	double old_dir_x;
	double old_plane_x;

	old_dir_x = player->dir_x;
	old_plane_x = player->plane_x;
	player->dir_x = player->dir_x * cos(-player->rot_speed) - player->dir_y
		* sin(-player->rot_speed);
	player->dir_y = old_dir_x * sin(-player->rot_speed) + player->dir_y
		* cos(-player->rot_speed);
	player->plane_x = player->plane_x * cos(-player->rot_speed) - player->plane_y
		* sin(-player->rot_speed);
	player->plane_y = old_plane_x * sin(-player->rot_speed) + player->plane_y
		* cos(-player->rot_speed);
}

void turn_left(t_player *player)
{
	double old_dir_x;
	double old_plane_x;

	old_dir_x = player->dir_x;
	old_plane_x = player->plane_x;
	player->dir_x = player->dir_x * cos(player->rot_speed) - player->dir_y
		* sin(player->rot_speed);
	player->dir_y = old_dir_x * sin(player->rot_speed) + player->dir_y
		* cos(player->rot_speed);
	player->plane_x = player->plane_x * cos(player->rot_speed) - player->plane_y
		* sin(player->rot_speed);
	player->plane_y = old_plane_x * sin(player->rot_speed) + player->plane_y
		* cos(player->rot_speed);
}
