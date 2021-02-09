/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hach <ael-hach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 14:52:31 by ael-hach          #+#    #+#             */
/*   Updated: 2021/02/09 16:09:10 by ael-hach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int		draw(t_game *game)
{
	t_player	*player;
	double		*z_buffer;

	z_buffer = malloc(sizeof(*z_buffer) * game->res.width);
	player = &game->player;
	draw_walls(game, z_buffer);
	draw_every_sprite(game, z_buffer, game->sprite_count);
	free(z_buffer);
	mlx_put_image_to_window(game->mlx, game->win, game->win_buffer.img, 0, 0);
	return (0);
}

void	my_mlx_pixel_put(t_game *game, int x, int y, int color)
{
	t_data	*buffer;

	buffer = &game->win_buffer;
	if (y < game->res.height && y >= 0)
		buffer->addr[(y) * game->res.width + (x)] = color;
}

void	draw_vertical_line(t_game *game, int x, t_interval range, int color)
{
	int	y;

	y = range.start;
	while (y < range.end)
	{
		my_mlx_pixel_put(game, x, y, color);
		y++;
	}
}
