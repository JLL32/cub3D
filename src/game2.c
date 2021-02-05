#include "../cub3D.h"

int on_key_press(int keycode, t_game *game)
{
	t_player *player;
	t_data *textures;

	player = &game->player;
	textures = game->textures;

	if (keycode == KEY_UP)
		move_up(player, game->world_map);
	if (keycode == KEY_DOWN)
		move_down(player, game->world_map);

	if (keycode == KEY_RIGHT)
		move_right(player, game->world_map);
	if (keycode == KEY_LEFT)
		move_left(player, game->world_map);

	if (keycode == KEY_D)
		turn_right(player);
	if (keycode == KEY_A)
		turn_left(player);

	if (keycode == KEY_ESC)
		exit_game(game, EXIT_SUCCESS);

	draw(game);
	return 0;
}

int on_red_cross_press(t_game *game)
{
	exit_game(game, EXIT_SUCCESS);
	return (0);
}