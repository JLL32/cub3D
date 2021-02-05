#include "../cub3D.h"

int main(int argc, char *argv[argc])
{
	t_game game = create_game(argc, argv);
	draw(&game);
	mlx_hook(game.win, 2, 0, on_key_press, &game);
	mlx_hook(game.win, 17, 0, on_red_cross_press, &game);
	if (game.is_save)
	{
		take_screenshot(game);
		exit_game(&game, EXIT_SUCCESS);
	}
	mlx_loop(game.mlx);
	return (0);
}
