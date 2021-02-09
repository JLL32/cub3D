#include "../cub3D.h"

/*
** translate sprite position to relative to camera
** transform sprite with the inverse camera matrix
**  [ planeX   dirX ] -1                                       [ dirY      -dirX ]
**  [               ]       =  1/(planeX*dirY-dirX*planeY) *   [                 ]
**  [ planeY   dirY ]                                          [ -planeY  planeX ]
*/

static t_coordinate get_transform(t_player player, t_coordinate sprites[], int sprite_order[], int i)
{
	double sprite_x;
	double sprite_y;
	double inv_det;
	t_coordinate transform;

	sprite_x = sprites[sprite_order[i]].x - player.pos_x;
	sprite_y = sprites[sprite_order[i]].y - player.pos_y;
	inv_det = 1.0 / (player.plane_x * player.dir_y - player.dir_x * player.plane_y);
	transform.x = inv_det * (player.dir_y * sprite_x - player.dir_x * sprite_y);
	transform.y = inv_det * (-player.plane_y * sprite_x + player.plane_x * sprite_y);
	return (transform);
}

/*
** calculates the lowest pixels to fill of a sprite's stripe
*/

static t_square get_sprite_draw_start(t_sprite sprite, t_resolution res)
{
	t_square draw_start;

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

static t_square get_sprite_draw_end(t_sprite sprite, t_resolution res)
{
	t_square draw_end;

	draw_end.y = sprite.res.height / 2 + res.height / 2;
	if (draw_end.y >= res.height)
		draw_end.y = res.height - 1;
	draw_end.x = sprite.res.width / 2 + sprite.screen_x;
	if (draw_end.x >= res.width)
		draw_end.x = res.width - 1;
	return (draw_end);
}

t_sprite get_sprite(t_game *game, int sprite_order[], int i)
{
	t_sprite sprite;
	sprite.x = game->sprite_positions[i].x;
	sprite.y = game->sprite_positions[i].y;
	sprite.trans = get_transform(game->player, game->sprite_positions, sprite_order, i);
	sprite.screen_x = (int)((game->res.width / 2) * (1 + sprite.trans.x / sprite.trans.y));
	sprite.res.height = abs((int)(game->res.height / sprite.trans.y));
	sprite.res.width = abs((int)(game->res.height / sprite.trans.y));
	sprite.draw_start = get_sprite_draw_start(sprite, game->res);
	sprite.draw_end = get_sprite_draw_end(sprite, game->res);
	return (sprite);
}

/*
** loops through every vertical stripe of the sprite on screen and draws it
** the conditions in the if are:
** 1) it's in front of camera plane so you don't see things behind you
** 2) it's on the screen (left)
** 3) it's on the screen (right)
** 4) ZBuffer, with perpendicular distance
*/

void draw_sprite(t_game *game, t_sprite sprite, double z_buffer[])
{
	t_square tex_px;
	int d;
	int color;
	int stripe;
	int y;

	stripe = sprite.draw_start.x;
	while (stripe < sprite.draw_end.x)
	{
		tex_px.x = (int)(256 * (stripe - (-sprite.res.width / 2 + sprite.screen_x)) * TEX_WIDTH / sprite.res.width) / 256;
		if (sprite.trans.y > 0 && stripe > 0 && stripe < game->res.width && sprite.trans.y < z_buffer[stripe])
		{
			y = sprite.draw_start.y;
			while (y < sprite.draw_end.y)
			{
				d = (y)*256 - game->res.height * 128 + sprite.res.height * 128;
				tex_px.y = ((d * TEX_HEIGHT) / sprite.res.height) / 256;
				color = game->textures[SP_TEX].addr[TEX_WIDTH * tex_px.y + tex_px.x];
				if ((color & 0x00FFFFFF) != 0)
					my_mlx_pixel_put(game, stripe, y, color);
				y++;
			}
		}
		stripe++;
	}
}