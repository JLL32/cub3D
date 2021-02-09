/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hach <ael-hach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 15:15:16 by ael-hach          #+#    #+#             */
/*   Updated: 2021/02/09 16:09:10 by ael-hach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

/*
** Jumps to the next map square, or in x_direction, or in y-direction
** and returns which side the ray has hit of the square (not necessarily a wall)
*/

static int			extend_ray(t_ray *ray)
{
	int	side;

	side = 0;
	if (ray->side_dist.x < ray->side_dist.y)
	{
		ray->side_dist.x += ray->delta_dist.x;
		ray->map_pos.x += ray->step_dir.x;
		if (ray->dir.x > 0)
			side = 0;
		else
			side = 2;
	}
	else
	{
		ray->side_dist.y += ray->delta_dist.y;
		ray->map_pos.y += ray->step_dir.y;
		if (ray->dir.y > 0)
			side = 1;
		else
			side = 3;
	}
	return (side);
}

/*
** detects any facing vertical stripe belonging to a wall
** and returns the necessary information to draw it:
** - the side where it was hit
** - the perpendicular distance from the projection plane
** - where exactly the wall was hit
** - the height of that wall stripe
*/

t_wall_stripe		cast_ray(t_player *player, t_resolution res,
	int x,
	char **world_map)
{
	t_ray		ray;
	int			side;
	double		wall_x;
	double		perp_wall_dist;

	ray = get_ray(*player, res.width, x);
	while (world_map[ray.map_pos.x][ray.map_pos.y] != '1')
		side = extend_ray(&ray);
	if (side % 2 == 0)
		perp_wall_dist = (ray.map_pos.x - player->pos_x +
				(1.0 - ray.step_dir.x) / 2) / ray.dir.x;
	else
		perp_wall_dist = (ray.map_pos.y - player->pos_y +
				(1.0 - ray.step_dir.y) / 2) / ray.dir.y;
	if (side % 2 == 0)
		wall_x = player->pos_y + perp_wall_dist * ray.dir.y;
	else
		wall_x = player->pos_x + perp_wall_dist * ray.dir.x;
	wall_x -= floor(wall_x);
	return ((t_wall_stripe){x, perp_wall_dist, side, wall_x,
				(int)(res.height /
				perp_wall_dist)});
}
