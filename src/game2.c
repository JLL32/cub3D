/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hach <ael-hach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 15:05:53 by ael-hach          #+#    #+#             */
/*   Updated: 2021/02/09 16:51:42 by ael-hach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int		on_key_press(int keycode, t_game *game)
{
	t_player	*player;
	t_data		*textures;

	player = &game->player;
	textures = game->textures;
	if (keycode == KEY_UP)
		move_up(player, game->world_map);
	if (keycode == KEY_DOWN)
		move_down(player, game->world_map);
	if (keycode == KEY_RIGHT)
		turn_right(player);
	if (keycode == KEY_LEFT)
		turn_left(player);
	if (keycode == KEY_D)
		move_right(player, game->world_map);
	if (keycode == KEY_A)
		move_left(player, game->world_map);
	if (keycode == KEY_ESC)
		exit_game(game, EXIT_SUCCESS);
	draw(game);
	return (0);
}

int		on_red_cross_press(t_game *game)
{
	exit_game(game, EXIT_SUCCESS);
	return (0);
}
