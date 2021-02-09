/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hach <ael-hach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 15:23:44 by ael-hach          #+#    #+#             */
/*   Updated: 2021/02/09 16:09:10 by ael-hach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

/*
** translate sprite position to relative to camera
** transform sprite with the inverse camera matrix
** [ planeX   dirX ] -1                                     [ dirY      -dirX ]
** [               ]     =  1/(planeX*dirY-dirX*planeY) *   [                 ]
** [ planeY   dirY ]                                        [ -planeY  planeX ]
*/

static t_coordinate		get_transform(t_player player, t_coordinate sprites[],
		int sprite_order[], int i)
{
	double			sprite_x;
	double			sprite_y;
	double			inv_det;
	t_coordinate	transform;

	sprite_x = sprites[sprite_order[i]].x - player.pos_x;
	sprite_y = sprites[sprite_order[i]].y - player.pos_y;
	inv_det = 1.0 /
		(player.plane_x * player.dir_y - player.dir_x * player.plane_y);
	transform.x = inv_det *
		(player.dir_y * sprite_x - player.dir_x * sprite_y);
	transform.y = inv_det *
		(-player.plane_y * sprite_x + player.plane_x * sprite_y);
	return (transform);
}

/*
** calculates the lowest pixels to fill of a sprite's stripe
*/

static t_square			get_sprite_draw_start(t_sprite sprite, t_resolution res)
{
	t_square	draw_start;

	draw_start.x = -sprite.res.width / 2 + sprite.screen_x;
	if (draw_start.x < 0)
		draw_start.x = 0;
	draw_start.y = -sprite.res.height / 2 + res.height / 2;
	if (draw_start.y < 0)
		draw_start.y = 0;
	return (draw_start);
}

/*
** calculates the highest pixels to fill of a sprite's stripe
*/

static t_square			get_sprite_draw_end(t_sprite sprite, t_resolution res)
{
	t_square	draw_end;

	draw_end.y = sprite.res.height / 2 + res.height / 2;
	if (draw_end.y >= res.height)
		draw_end.y = res.height - 1;
	draw_end.x = sprite.res.width / 2 + sprite.screen_x;
	if (draw_end.x >= res.width)
		draw_end.x = res.width - 1;
	return (draw_end);
}

t_sprite				get_sprite(t_game *game, int sprite_order[], int i)
{
	t_sprite	sprite;

	sprite.x = game->sprite_positions[i].x;
	sprite.y = game->sprite_positions[i].y;
	sprite.trans =
		get_transform(game->player, game->sprite_positions, sprite_order, i);
	sprite.screen_x =
		(int)((game->res.width / 2) * (1 + sprite.trans.x / sprite.trans.y));
	sprite.res.height = abs((int)(game->res.height / sprite.trans.y));
	sprite.res.width = abs((int)(game->res.height / sprite.trans.y));
	sprite.draw_start = get_sprite_draw_start(sprite, game->res);
	sprite.draw_end = get_sprite_draw_end(sprite, game->res);
	return (sprite);
}
