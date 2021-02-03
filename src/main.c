#include "../cub3D.h"
#include <stdlib.h>

#define SPR_TEX_INDX 4



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
	mlx_destroy_image(game->mlx, game->textures[0].img);
	mlx_destroy_image(game->mlx, game->textures[1].img);
	mlx_destroy_image(game->mlx, game->textures[2].img);
	mlx_destroy_image(game->mlx, game->textures[3].img);
	mlx_destroy_image(game->mlx, game->textures[4].img);
	mlx_destroy_image(game->mlx, game->win_buffer.img);
	mlx_destroy_window(game->mlx, game->win);
	exit(status);
}

int red_cross_press(t_game *game)
{
	exit_game(game, EXIT_SUCCESS);
	return (0);
}

// function used to sort the sprites
void sort_sprites(int *order, double *dist, int amount);

int draw(t_game *game);
t_ray cast_ray(t_player player, int win_width, int x);
void my_mlx_pixel_put(t_game *game, int x, int y, int color)
{
	t_data *buffer = &game->win_buffer;
	if (y < game->res.height && y >= 0)
		buffer->addr[(y)*game->res.width + (x)] = color;
}

int key_press(int keycode, t_game *game)
{
	t_player *player = &game->player;
	t_data *textures = game->textures;
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

	// TODO: don't forget to add escape and cross-red events which
	// are quiting the game and cleaning after (imgs, textures, sprites...)

	draw(game);
	return 0;
}



//sort algorithm
//sort the sprites based on distance
typedef struct s_pair
{
	double first;
	int second;
} t_pair;

void swap(t_pair *xp, t_pair *yp)
{
	t_pair temp = *xp;
	*xp = *yp;
	*yp = temp;
}
// A function to implement bubble sort
void pair_sort(t_pair arr[], int n)
{
	int i, j;
	for (i = 0; i < n - 1; i++)
		for (j = 0; j < n - i - 1; j++)
			if (arr[j].first > arr[j + 1].first)
				swap(&arr[j], &arr[j + 1]);
}

// sorts sprites from for to close
void sort_sprites(int *order, double *dist, int amount)
{
	/* std::vector<std::pair<double, int>> sprites(amount); */
	t_pair sprites[amount];
	for (int i = 0; i < amount; i++)
	{
		sprites[i].first = dist[i];
		sprites[i].second = order[i];
	}
	pair_sort(sprites, amount);
	// restore in reverse order to go from farthest to nearest
	for (int i = 0; i < amount; i++)
	{
		dist[i] = sprites[amount - i - 1].first;
		order[i] = sprites[amount - i - 1].second;
	}
}

// performs DDA
t_wall_stripe detect_wall(t_player *player, t_resolution res, int x , char **world_map)
{
	t_ray ray = cast_ray(*player, res.width, x);
	int side;	 //was a NS or a EW wall hit?
	int hit = 0; //was there a wall hit?
	double wall_x; // where exactly the wall was hit

	double perp_wall_dist;
	while (hit == 0)
	{
		/*jump to next map square, or in x_direction, or in y-direction*/
		if (ray.side_dist.x < ray.side_dist.y)
		{
			ray.side_dist.x += ray.delta_dist.x;
			ray.map_pos.x += ray.step_dir.x;
			if (ray.dir.x > 0)
				side = 0;
			else
				side = 2;
		}
		else
		{
			ray.side_dist.y += ray.delta_dist.y;
			ray.map_pos.y += ray.step_dir.y;
			if (ray.dir.y > 0)
				side = 1;
			else
				side = 3;
		}
		/*check if ray has hit a wall*/
		if (world_map[ray.map_pos.x][ray.map_pos.y] == '1')
			hit = 1;
	}
	//Calculate the distance projected on camera direction (Euclidean distance will give fisheye effect!)*/
	if (side % 2 == 0)
		perp_wall_dist = (ray.map_pos.x - player->pos_x + (1.0 - ray.step_dir.x) / 2) / ray.dir.x;
	else
		perp_wall_dist = (ray.map_pos.y - player->pos_y + (1.0 - ray.step_dir.y) / 2) / ray.dir.y;

	if (side % 2 == 0)
		wall_x = player->pos_y + perp_wall_dist * ray.dir.y;
	else
		wall_x = player->pos_x + perp_wall_dist * ray.dir.x;
	wall_x -= floor(wall_x);

	/* calculate line_height */
	int line_height = (int)(res.height / perp_wall_dist);
	return ((t_wall_stripe){perp_wall_dist, side, wall_x, line_height});
}

//calculate ray position and direction
t_coordinate get_ray_dir(t_player player, int win_width, int x)
{
	double camera_x;
	t_coordinate ray_dir;

	camera_x = 2 * x / (double)win_width - 1; //x-coordinate in camera space
	ray_dir.x = player.dir_x + player.plane_x * camera_x;
	ray_dir.y = player.dir_y + player.plane_y * camera_x;
	return ray_dir;
}

//which square of the map we're in
t_square pos_to_map_pos(t_player player)
{

	return ((t_square){player.pos_x, player.pos_y});
}

//length of ray from one x or y-side to next x or y-side
t_coordinate get_delta_dist(t_coordinate ray_dir)
{
	return ((t_coordinate){fabs(1.0 / ray_dir.x), fabs(1.0 / ray_dir.y)});
}

//length of ray from current position to next x or y-side
t_coordinate get_side_dist(t_coordinate delta_dist,t_coordinate ray_dir,
		t_square map, t_player player)
{
	t_coordinate side_dist;

	if (ray_dir.x < 0)
	{
		side_dist.x = (player.pos_x - map.x) * delta_dist.x;
	}
	else
	{
		side_dist.x = (map.x + 1.0 - player.pos_x) * delta_dist.x;
	}
	if (ray_dir.y < 0)
	{
		side_dist.y = (player.pos_y - map.y) * delta_dist.y;
	}
	else
	{
		side_dist.y = (map.y + 1.0 - player.pos_y) * delta_dist.y;
	}
	return side_dist;
}

//what direction to step in x or y-direction (either +1 or -1)
t_square get_step_dir(t_coordinate ray_dir)
{
	t_square step_dir;

	if (ray_dir.x < 0)
	{
		step_dir.x = -1;
	}
	else
	{
		step_dir.x = 1;
	}
	if (ray_dir.y < 0)
	{
		step_dir.y = -1;
	}
	else
	{
		step_dir.y = 1;
	}
	return step_dir;
}

t_ray cast_ray(t_player player, int win_width, int x)
{
	t_ray ray;
	ray.dir = get_ray_dir(player, win_width, x);
	ray.map_pos = pos_to_map_pos(player);
	ray.delta_dist = get_delta_dist(ray.dir);
	ray.side_dist = get_side_dist(ray.delta_dist, ray.dir, ray.map_pos, player);
	ray.step_dir = get_step_dir(ray.dir);
	return (ray);
}

/*calculate the lowest and highest pixel fo fill in the current stripe*/
t_interval get_drawing_interval(int win_height, int stripe_height)
{
	t_interval interval;
	interval.start = -stripe_height / 2 + win_height / 2;
	if (interval.start < 0)
		interval.start = 0;
	interval.end = stripe_height / 2 + win_height / 2;
	if (interval.end >= win_height)
		interval.end = win_height - 1;
	return  (interval);
}

t_tex_stripe get_tex_stripe(t_wall_stripe stripe, int height, t_interval draw)
{
	// x coordinate on the texture
	int tex_x;
	// How much to increase the texture coordinate per screen pixel
	double step;
	// Starting texture coordinat
	double pos;
	tex_x = (int)(stripe.wall_x * (double)(tex_width));
	if (stripe.side == 0)
		tex_x = tex_width - tex_x - 1;
	if (stripe.side == 3)
		tex_x = tex_width - tex_x - 1;

	step = 1.0 * tex_height / stripe.height;
	pos = (draw.start - height / 2.0 + stripe.height / 2.0) * step;
	return ((t_tex_stripe){tex_x, 0, pos, step});
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
void draw_tex_stripe(t_game *game,t_wall_stripe stripe, t_tex_stripe tex, int x, t_interval draw)
{
	int color;
	int y;

	y = draw.start;
	while (y < draw.end)
	{
		// cast the texture coordinat to integer, and mask with (tex_height - 1) in case of overflow
		tex.y = (int)tex.pos & (tex_height - 1);
		tex.pos += tex.step;
		color = game->textures[stripe.side].addr[tex_height * tex.y + tex.x];
		my_mlx_pixel_put(game, x, y, color);
		y++;
	}
}

void draw_walls(t_game *game, double z_buffer[])
{
	t_wall_stripe stripe;
	t_interval draw;
	t_tex_stripe tex;
	int x;

	x = 0;
	while (x < game->res.width)
	{
		// if (game->sprite_positions[0].x != 3.5)
		// {
		// 	printf("%d", x);
		// 	exit(0);
		// }
		stripe = detect_wall(&game->player, game->res, x, game->world_map);
		draw = get_drawing_interval(game->res.height, stripe.height);
		tex = get_tex_stripe(stripe, game->res.height, draw);
		draw_vertical_line(game, x, 0, draw.start, game->colors.ceiling);
		draw_tex_stripe(game, stripe, tex, x, draw);
		draw_vertical_line(game, x, draw.end, game->res.height, game->colors.floor);
		z_buffer[x] = stripe.dist;
		x++;
	}
}

void populate_order(int sprite_order[], int num)
{
	int i;

	i = 0;
	while (i < num)
	{
		sprite_order[i] = i;
		i++;
	}
}

void populate_distance(t_player player, double sprite_distance[], t_coordinate sprites[], int num)
{
	int i;

	i = 0;
	while (i < num)
	{
		sprite_distance[i] = ((player.pos_x - sprites[i].x) * (player.pos_x - sprites[i].x) + (player.pos_y - sprites[i].y) * (player.pos_y - sprites[i].y));
		i++;
	}
}

t_coordinate get_transform(t_player player, t_coordinate sprites[], int sprite_order[], int i)
{

	double sprite_x;
	double sprite_y;
	double inv_det;
	t_coordinate transform;

	// translate sprite position to relative to camera
	sprite_x = sprites[sprite_order[i]].x - player.pos_x;
	sprite_y = sprites[sprite_order[i]].y - player.pos_y;

	//transform sprite with the inverse camera matrix
	// [ planeX   dirX ] -1                                       [ dirY      -dirX ]
	// [               ]       =  1/(planeX*dirY-dirX*planeY) *   [                 ]
	// [ planeY   dirY ]                                          [ -planeY  planeX ]
	inv_det = 1.0 / (player.plane_x * player.dir_y - player.dir_x * player.plane_y); // required for correct matrix multiplication

	transform.x = inv_det * (player.dir_y * sprite_x - player.dir_x * sprite_y);
	transform.y = inv_det * (-player.plane_y * sprite_x + player.plane_x * sprite_y);

	return (transform);
}

// calculates the lowest pixels to fill of a sprite's stripe
t_square get_sprite_draw_start(t_sprite sprite, t_resolution res)
{
	t_square draw_start;

	draw_start.x = -sprite.res.width / 2 + sprite.screen_x;
	if (draw_start.x < 0)
		draw_start.x = 0;
	draw_start.y = -sprite.res.height / 2 + res.height / 2;
	if (draw_start.y < 0)
		draw_start.y = 0;
	return (draw_start);
}

// calculates the highest pixels to fill of a sprite's stripe
t_square get_sprite_draw_end(t_sprite sprite, t_resolution res)
{
	t_square draw_end;

	draw_end.y = sprite.res.height / 2 + res.height / 2;
	if (draw_end.y >= res.height)
		draw_end.y = res.height - 1;
	draw_end.x = sprite.res.width / 2 + sprite.screen_x;
	if (draw_end.x >= res.width)
		draw_end.x = res.width - 1;
	return (draw_end);
}

t_sprite get_sprite(t_game *game, int sprite_order[], int i)
{
	t_sprite sprite;
	sprite.x = game->sprite_positions[i].x;
	sprite.y = game->sprite_positions[i].y;
	sprite.trans = get_transform(game->player, game->sprite_positions, sprite_order, i);
	sprite.screen_x = (int)((game->res.width / 2) * (1 + sprite.trans.x / sprite.trans.y));
	sprite.res.height = abs((int)(game->res.height / sprite.trans.y));
	sprite.res.width = abs((int)(game->res.height / sprite.trans.y));
	sprite.draw_start = get_sprite_draw_start(sprite, game->res);
	sprite.draw_end = get_sprite_draw_end(sprite, game->res);
	return (sprite);
}

//loops through every vertical stripe of the sprite on screen and draws it
//the conditions in the if are:
//1) it's in front of camera plane so you don't see things behind you
//2) it's on the screen (left)
//3) it's on the screen (right)
//4) ZBuffer, with perpendicular distance
void draw_sprite(t_game *game, t_sprite sprite, double z_buffer[])
{
	t_square tex_px;
	int d;
	int color;
	int stripe;
	int y;

	stripe = sprite.draw_start.x;
	while (stripe < sprite.draw_end.x)
	{
		tex_px.x = (int)(256 * (stripe - (-sprite.res.width / 2 + sprite.screen_x)) * tex_width / sprite.res.width) / 256;
		if (sprite.trans.y > 0 && stripe > 0 && stripe < game->res.width && sprite.trans.y < z_buffer[stripe])
		{
			y = sprite.draw_start.y;
			while (y < sprite.draw_end.y) //for every pixel of the current stripe
			{
				d = (y)*256 - game->res.height * 128 + sprite.res.height * 128; //256 and 128 factors to avoid floats
				tex_px.y = ((d * tex_height) / sprite.res.height) / 256;
				color = game->textures[SPR_TEX_INDX].addr[tex_width * tex_px.y + tex_px.x]; //get current color from the texture
				if ((color & 0x00FFFFFF) != 0)
					my_mlx_pixel_put(game, stripe, y, color); //paint pixel if it isn't black, black is the invisible color
				y++;
			}
		}
		stripe++;
	}
}

void draw_every_sprite(t_game *game, double z_buffer[], int num)
{
	// arrays used to sort the sprites
	t_sprite sprite;
	int sprite_order[num];
	double sprite_distance[num];
	int i;

	populate_order(sprite_order, num);
	populate_distance(game->player, sprite_distance, game->sprite_positions, num);
	sort_sprites(sprite_order, sprite_distance, num);

	// after sorting the sprites do the projection and draw them
	i = 0;
	while (i < num)
	{
		sprite = get_sprite(game, sprite_order, i);
		draw_sprite(game, sprite, z_buffer);
		i++;
	}
}

int draw(t_game *game)
{
	t_player *player = &game->player;
	double z_buffer[game->res.width];

	draw_walls(game, z_buffer);

	draw_every_sprite(game, z_buffer, game->sprite_count);
	mlx_put_image_to_window(game->mlx, game->win, game->win_buffer.img, 0, 0);
	return 0;
}
void load_textures(t_textures_paths paths, t_data *textures, void *mlx)
{
	textures[0].img = mlx_xpm_file_to_image(mlx, paths.so, &textures[0].width, &textures[0].height);
	textures[0].addr = (int *)mlx_get_data_addr(textures[0].img, &textures[0].bits_per_pixel, &textures[0].line_length, &textures[0].endian);

	textures[1].img = mlx_xpm_file_to_image(mlx, paths.ea, &textures[1].width, &textures[1].height);
	textures[1].addr = (int *)mlx_get_data_addr(textures[1].img, &textures[1].bits_per_pixel, &textures[1].line_length, &textures[1].endian);

	textures[2].img = mlx_xpm_file_to_image(mlx, paths.no, &textures[2].width, &textures[2].height);
	textures[2].addr = (int *)mlx_get_data_addr(textures[2].img, &textures[2].bits_per_pixel, &textures[2].line_length, &textures[2].endian);

	textures[3].img = mlx_xpm_file_to_image(mlx, paths.we, &textures[3].width, &textures[3].height);
	textures[3].addr = (int *)mlx_get_data_addr(textures[3].img, &textures[3].bits_per_pixel, &textures[3].line_length, &textures[3].endian);

	textures[4].img = mlx_xpm_file_to_image(mlx, paths.sp, &textures[4].width, &textures[4].height);
	textures[4].addr = (int *)mlx_get_data_addr(textures[4].img, &textures[4].bits_per_pixel, &textures[4].line_length, &textures[4].endian);
	free(paths.no);
	free(paths.we);
	free(paths.so);
	free(paths.ea);
	free(paths.sp);
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
	load_textures(cfg.tex, game.textures, game.mlx);
	return (game);
}



int main(int argc, char *argv[argc])
{
	t_game game = create_game(argc, argv);

	draw(&game);

	mlx_hook(game.win, 2, 0, key_press, &game);
	mlx_hook(game.win, 17, 0, red_cross_press, &game);

	mlx_loop(game.mlx);

	return (0);
}
