#include "../cub3D.h"

//calculate ray position and direction
static t_coordinate get_ray_dir(t_player player, int win_width, int x)
{
	double camera_x;
	t_coordinate ray_dir;

	camera_x = 2 * x / (double)win_width - 1; //x-coordinate in camera space
	ray_dir.x = player.dir_x + player.plane_x * camera_x;
	ray_dir.y = player.dir_y + player.plane_y * camera_x;
	return ray_dir;
}

//length of ray from current position to next x or y-side
static t_coordinate get_side_dist(t_coordinate delta_dist,t_coordinate ray_dir,
		t_square map, t_player player)
{
	t_coordinate side_dist;

	if (ray_dir.x < 0)
	{
		side_dist.x = (player.pos_x - map.x) * delta_dist.x;
	}
	else
	{
		side_dist.x = (map.x + 1.0 - player.pos_x) * delta_dist.x;
	}
	if (ray_dir.y < 0)
	{
		side_dist.y = (player.pos_y - map.y) * delta_dist.y;
	}
	else
	{
		side_dist.y = (map.y + 1.0 - player.pos_y) * delta_dist.y;
	}
	return side_dist;
}

//what direction to step in x or y-direction (either +1 or -1)
static t_square get_step_dir(t_coordinate ray_dir)
{
	t_square step_dir;

	if (ray_dir.x < 0)
	{
		step_dir.x = -1;
	}
	else
	{
		step_dir.x = 1;
	}
	if (ray_dir.y < 0)
	{
		step_dir.y = -1;
	}
	else
	{
		step_dir.y = 1;
	}
	return step_dir;
}

t_ray cast_ray(t_player player, int win_width, int x)
{
	t_ray ray;
	ray.dir = get_ray_dir(player, win_width, x);
	ray.map_pos = (t_square){player.pos_x, player.pos_y};
	ray.delta_dist = (t_coordinate){fabs(1.0 / ray.dir.x),
		fabs(1.0 / ray.dir.y)};
	ray.side_dist = get_side_dist(ray.delta_dist, ray.dir, ray.map_pos, player);
	ray.step_dir = get_step_dir(ray.dir);
	return (ray);
}

