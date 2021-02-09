/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hach <ael-hach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 14:34:02 by ael-hach          #+#    #+#             */
/*   Updated: 2021/02/09 16:12:24 by ael-hach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

/*
** returns necessary info to draw texture stripe:
** - x coordinate on the texture
** - How much to increase the texture coordinate per screen pixel
** - Starting texture coordinate
*/

static t_tex_stripe	get_tex_stripe(t_wall_stripe stripe,
									int height,
									t_interval draw)
{
	int		tex_x;
	double	step;
	double	pos;

	tex_x = (int)(stripe.wall_x * (double)(TEX_WIDTH));
	if (stripe.side == 0)
		tex_x = TEX_WIDTH - tex_x - 1;
	if (stripe.side == 3)
		tex_x = TEX_WIDTH - tex_x - 1;
	step = 1.0 * TEX_HEIGHT / stripe.height;
	pos = (draw.start - height / 2.0 + stripe.height / 2.0) * step;
	return ((t_tex_stripe){tex_x, 0, pos, step});
}

static void			draw_tex_stripe(t_game *game,
									t_wall_stripe stripe,
									t_tex_stripe tex,
									t_interval draw)
{
	int	color;
	int	y;

	y = draw.start;
	while (y < draw.end)
	{
		tex.y = (int)tex.pos & (TEX_HEIGHT - 1);
		tex.pos += tex.step;
		color = game->textures[stripe.side].addr[TEX_HEIGHT * tex.y + tex.x];
		my_mlx_pixel_put(game, stripe.x, y, color);
		y++;
	}
}

/*
** calculate the lowest and highest pixel fo fill in the current stripe
*/

static t_interval	get_drawing_interval(int win_height, int stripe_height)
{
	t_interval	interval;

	interval.start = -stripe_height / 2 + win_height / 2;
	if (interval.start < 0)
		interval.start = 0;
	interval.end = stripe_height / 2 + win_height / 2;
	if (interval.end >= win_height)
		interval.end = win_height - 1;
	return (interval);
}

void				draw_walls(t_game *game, double z_buffer[])
{
	t_wall_stripe	stripe;
	t_interval		draw;
	t_tex_stripe	tex;
	int				x;

	x = 0;
	while (x < game->res.width)
	{
		stripe = cast_ray(&game->player, game->res, x, game->world_map);
		draw = get_drawing_interval(game->res.height, stripe.height);
		tex = get_tex_stripe(stripe, game->res.height, draw);
		draw_vertical_line(game, x, (t_interval){0, draw.start},
			game->colors.ceiling);
		draw_tex_stripe(game, stripe, tex, draw);
		draw_vertical_line(game, x, (t_interval){draw.end, game->res.height},
				game->colors.floor);
		z_buffer[x] = stripe.dist;
		x++;
	}
}
