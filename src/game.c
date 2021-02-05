#include "../cub3D.h"

void exit_game(t_game *game, int status)
{
	int i;

	i = 0;
	while (game->world_map[i])
	{
		free(game->world_map[i]);
		i++;
	}
	free(game->world_map);
	i = 0;
	while (i < 5)
	{
		if (game->textures[i].img)
			mlx_destroy_image(game->mlx, game->textures[i].img);
		i++;
	}
	mlx_destroy_image(game->mlx, game->win_buffer.img);
	mlx_destroy_window(game->mlx, game->win);
	exit(status);
}

static void init_textures(t_data *textures)
{
	textures[0].img = NULL;
	textures[1].img = NULL;
	textures[2].img = NULL;
	textures[3].img = NULL;
	textures[4].img = NULL;
}

static t_data load_texture(char *path, t_game *game)
{
	t_data texture_buffer;
	texture_buffer.img = mlx_xpm_file_to_image(game->mlx, path,
	 	&texture_buffer.width, &texture_buffer.height);
	free(path);
	if(texture_buffer.img == NULL
	|| texture_buffer.width != 64
	|| texture_buffer.height != 64)
	{
		ft_putstr_fd("ERROR: Invalid texture", 2);
		exit_game(game, EXIT_FAILURE);
	}
	texture_buffer.addr = (int *)mlx_get_data_addr(texture_buffer.img,
	 	&texture_buffer.bits_per_pixel, &texture_buffer.line_length, 
	 	&texture_buffer.endian);
	return (texture_buffer);
}

static void load_textures(t_textures_paths paths, t_game *game)
{
	init_textures(game->textures);
	game->textures[0] = load_texture(paths.no, game);
	game->textures[1] = load_texture(paths.we, game);
	game->textures[2] = load_texture(paths.so, game);
	game->textures[3] = load_texture(paths.ea, game);
	game->textures[4] = load_texture(paths.sp, game);
}

t_game create_game(int argc, char **argv)
{
	t_game game;
	t_config cfg;
	cfg = parse_file(argc, argv);
	game.player = create_player(cfg.player.pos_x, cfg.player.pos_y, cfg.player.dir);
	game.colors = cfg.colors;
	game.res = cfg.res;
	game.world_map = cfg.map;
	ft_memcpy(game.sprite_positions, cfg.sprites, cfg.sprite_count*sizeof(t_coordinate));
	game.sprite_count = cfg.sprite_count;
	game.is_save = cfg.is_save;
	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, game.res.width, game.res.height, "Cub3D");
	game.win_buffer.img = mlx_new_image(game.mlx, game.res.width, game.res.height);
	game.win_buffer.addr = (int *)mlx_get_data_addr(game.win_buffer.img,
	&game.win_buffer.bits_per_pixel, &game.win_buffer.line_length, &game.win_buffer.endian);
	load_textures(cfg.tex, &game);
	return (game);
}

