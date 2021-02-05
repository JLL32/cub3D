#include "../cub3D.h"

int draw(t_game *game)
{
	t_player *player = &game->player;
	double z_buffer[game->res.width];

	draw_walls(game, z_buffer);

	draw_every_sprite(game, z_buffer, game->sprite_count);
	mlx_put_image_to_window(game->mlx, game->win, game->win_buffer.img, 0, 0);
	return 0;
}

void my_mlx_pixel_put(t_game *game, int x, int y, int color)
{
	t_data *buffer = &game->win_buffer;
	if (y < game->res.height && y >= 0)
		buffer->addr[(y)*game->res.width + (x)] = color;
}

void draw_vertical_line(t_game *game, int x, int start, int end, int color)
{
	int y = start;
	while (y < end)
	{
		my_mlx_pixel_put(game, x, y, color);
		y++;
	}
}