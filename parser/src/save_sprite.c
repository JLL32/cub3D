#include "../parser.h"

static void	get_sprite_pos(t_config *config, int i, int j)
{
	config->sprites[config->sprite_count].x = j + 0.5;
	config->sprites[config->sprite_count].y = i + 0.5;
	config->sprite_count++;
}

int		is_sprite(t_config *config, int i, int j)
{
	char **map;

	map = config->map;
	if (map[i][j] == '2')
	{
		get_sprite_pos(config, i, j);
		return (1);
	}
	return (0);
}