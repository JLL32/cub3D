/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hach <ael-hach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 14:31:13 by ael-hach          #+#    #+#             */
/*   Updated: 2021/02/09 16:12:16 by ael-hach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

static void			populate_order(int sprite_order[], int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		sprite_order[i] = i;
		i++;
	}
}

static void			populate_distance(t_player player,
								double sprite_distance[],
								t_coordinate sprites[],
								int num)
{
	int i;

	i = 0;
	while (i < num)
	{
		sprite_distance[i] =
			((player.pos_x - sprites[i].x) * (player.pos_x - sprites[i].x) +
			(player.pos_y - sprites[i].y) * (player.pos_y - sprites[i].y));
		i++;
	}
}

static void			draw_sprite_stripe(t_sprite sprite,
			t_game *game,
			t_square tex_px,
			int stripe)
{
	int	y;
	int	color;
	int	d;

	y = sprite.draw_start.y;
	while (y < sprite.draw_end.y)
	{
		d = (y) * 256 - game->res.height *
			128 + sprite.res.height * 128;
		tex_px.y = ((d * TEX_HEIGHT) / sprite.res.height) / 256;
		color = game->textures[4].addr[TEX_WIDTH * tex_px.y + tex_px.x];
		if ((color & 0x00FFFFFF) != 0)
			my_mlx_pixel_put(game, stripe, y, color);
		y++;
	}
}

/*
** loops through every vertical stripe of the sprite on screen and draws it
** the conditions in the if are:
** 1) it's in front of camera plane so you don't see things behind you
** 2) it's on the screen (left)
** 3) it's on the screen (right)
** 4) ZBuffer, with perpendicular distance
*/

static void			draw_sprite(t_game *game, t_sprite sprite,
		double z_buffer[])
{
	t_square	tex_px;
	int			d;
	int			color;
	int			stripe;
	int			y;

	stripe = sprite.draw_start.x;
	while (stripe < sprite.draw_end.x)
	{
		tex_px.x =
		(int)(256 * (stripe - (-sprite.res.width / 2 + sprite.screen_x))
		* TEX_WIDTH / sprite.res.width) / 256;
		if (sprite.trans.y > 0 && stripe > 0 && stripe < game->res.width
			&& sprite.trans.y < z_buffer[stripe])
		{
			draw_sprite_stripe(sprite, game, tex_px, stripe);
		}
		stripe++;
	}
}

void				draw_every_sprite(t_game *game, double z_buffer[], int num)
{
	t_sprite	sprite;
	int			sprite_order[num];
	double		sprite_distance[num];
	int			i;

	populate_order(sprite_order, num);
	populate_distance(game->player,
		sprite_distance,
		game->sprite_positions,
		num);
	sort_sprites(sprite_order, sprite_distance, num);
	i = 0;
	while (i < num)
	{
		sprite = get_sprite(game, sprite_order, i);
		draw_sprite(game, sprite, z_buffer);
		i++;
	}
}
