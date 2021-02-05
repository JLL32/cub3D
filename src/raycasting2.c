#include "../cub3D.h"

// performs DDA
t_wall_stripe detect_wall(t_player *player, t_resolution res, int x , char **world_map)
{
	t_ray ray = cast_ray(*player, res.width, x);
	int side;	 //was a NS or a EW wall hit?
	int hit = 0; //was there a wall hit?
	double wall_x; // where exactly the wall was hit

	double perp_wall_dist;
	while (hit == 0)
	{
		/*jump to next map square, or in x_direction, or in y-direction*/
		if (ray.side_dist.x < ray.side_dist.y)
		{
			ray.side_dist.x += ray.delta_dist.x;
			ray.map_pos.x += ray.step_dir.x;
			if (ray.dir.x > 0)
				side = 0;
			else
				side = 2;
		}
		else
		{
			ray.side_dist.y += ray.delta_dist.y;
			ray.map_pos.y += ray.step_dir.y;
			if (ray.dir.y > 0)
				side = 1;
			else
				side = 3;
		}
		/*check if ray has hit a wall*/
		if (world_map[ray.map_pos.x][ray.map_pos.y] == '1')
			hit = 1;
	}
	//Calculate the distance projected on camera direction (Euclidean distance will give fisheye effect!)*/
	if (side % 2 == 0)
		perp_wall_dist = (ray.map_pos.x - player->pos_x + (1.0 - ray.step_dir.x) / 2) / ray.dir.x;
	else
		perp_wall_dist = (ray.map_pos.y - player->pos_y + (1.0 - ray.step_dir.y) / 2) / ray.dir.y;

	if (side % 2 == 0)
		wall_x = player->pos_y + perp_wall_dist * ray.dir.y;
	else
		wall_x = player->pos_x + perp_wall_dist * ray.dir.x;
	wall_x -= floor(wall_x);

	/* calculate line_height */
	int line_height = (int)(res.height / perp_wall_dist);
	return ((t_wall_stripe){perp_wall_dist, side, wall_x, line_height});
}