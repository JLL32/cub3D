/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jll32 <jll32@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 12:48:33 by jll32             #+#    #+#             */
/*   Updated: 2021/02/07 17:07:37 by jll32            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

static void		get_player_pos_map(t_config *config, int i, int j)
{
	char			**map;
	t_player_pos	*player;

	map = config->map;
	player = &config->player;
	player->pos_x = i + .5;
	player->pos_y = j + .5;
	player->dir = map[i][j];
	map[i][j] = '0';
}

int				is_player(t_config *config, int i, int j)
{
	char	**map;

	map = config->map;
	if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E' ||
		map[i][j] == 'W')
	{
		if (g_player_num > 0)
			ft_error(config->map, "Error\nDuplicated player");
		get_player_pos_map(config, i, j);
		g_player_num++;
		return (1);
	}
	return (0);
}
