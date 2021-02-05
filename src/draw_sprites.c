#include "../cub3D.h"

static void populate_order(int sprite_order[], int num)
{
	int i;

	i = 0;
	while (i < num)
	{
		sprite_order[i] = i;
		i++;
	}
}

static void populate_distance(t_player player, double sprite_distance[], t_coordinate sprites[], int num)
{
	int i;

	i = 0;
	while (i < num)
	{
		sprite_distance[i] = ((player.pos_x - sprites[i].x) * (player.pos_x - sprites[i].x) + (player.pos_y - sprites[i].y) * (player.pos_y - sprites[i].y));
		i++;
	}
}

void draw_every_sprite(t_game *game, double z_buffer[], int num)
{
	// arrays used to sort the sprites
	t_sprite sprite;
	int sprite_order[num];
	double sprite_distance[num];
	int i;

	populate_order(sprite_order, num);
	populate_distance(game->player, sprite_distance, game->sprite_positions, num);
	sort_sprites(sprite_order, sprite_distance, num);

	// after sorting the sprites do the projection and draw them
	i = 0;
	while (i < num)
	{
		sprite = get_sprite(game, sprite_order, i);
		draw_sprite(game, sprite, z_buffer);
		i++;
	}
}