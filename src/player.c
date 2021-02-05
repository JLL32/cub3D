#include "../cub3D.h"

t_player create_player(double x, double y, char dir)
{
	t_player player;
	if (dir == 'N')
	{
		player = (t_player){x, y, -1, 0, MOVE_SPD, ROT_SPD, 0, PLANE};
	}
	else if (dir == 'W')
	{
		player = (t_player){x, y, 0, -1, MOVE_SPD, ROT_SPD, -PLANE, 0};
	}
	else if (dir == 'S')
	{
		player = (t_player){x, y, 1, 0, MOVE_SPD, ROT_SPD, 0, -PLANE};
	}
	else if (dir == 'E')
	{
		player = (t_player){x, y, 0, 1, MOVE_SPD, ROT_SPD, PLANE, 0};
	}
	return (player);
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
