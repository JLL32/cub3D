/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hach <ael-hach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 15:06:41 by ael-hach          #+#    #+#             */
/*   Updated: 2021/02/09 16:09:10 by ael-hach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	main(int argc, char *argv[argc])
{
	t_game	game;

	game = create_game(argc, argv);
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
