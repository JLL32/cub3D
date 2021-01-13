#include "cub3D.h"
#include "mlx/mlx.h"

typedef struct  s_vars {
	void        *mlx;
	void        *win;
}               t_vars;

typedef struct  s_data {
	void        *img;
	int        *addr;
	int         bits_per_pixel;
	int         line_length;
	int         endian;
}               t_data;

typedef int t_hex_color;

enum colors {
	red		= 0x0FF0000,
	maroon	= 0x0800000,
	yellow	= 0x0FFFF00,
	blue	= 0x00000FF,
	white	= 0xFFFFFFF,
	green	= 0x0008000,
	black	= 0x0000000,
	light_blue = 0xADD8E6,
	gray = 0x5A5A5A,
};

enum keys {
	arrow_up = 126,
	arrow_down = 125,
	arrow_right = 124,
	arrow_left = 123,
	a = 0,
	s = 1,
	w = 13,
	d = 2,
	escape = 53,
};

typedef struct s_player {
	double pos_x;
	double pos_y;
	double dir_x;
	double dir_y;
	double move_speed;
	double rot_speed;
} t_player;

t_data  img;

t_vars vars;

double plane_x, plane_y; /*the 2D raycaster version of camera plane*/

void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	if (y < screen_height && y >= 0)
		data->addr[(y) * screen_width + (x)] = color;
}

/* void vertical_line(int x, int draw_start, int draw_end, t_hex_color color, t_vars vars, t_data *img) */
/* { */
/* 	int y = draw_start; */
/* 	while (y <= draw_end) */
/* 	{ */
/* 		my_mlx_pixel_put(img, x, y, color); */
/* 		y++; */
/* 	} */
/* } */
void horizontal_line(int y, int draw_start, int draw_end, t_hex_color color, t_vars vars, t_data *img)
{
	int x = draw_start;
	while (x <= draw_end)
	{
		my_mlx_pixel_put(img, x, y, color);
		x++;
	}
	
}

// draws the whole scene so we won't need to clear after each frame
void vertical_line(int x, int draw_start, int draw_end, t_hex_color color, t_vars vars, t_data *img)
{
	// TODO: get floor and ceiling colors from an external variable not the colors enum
	int y = 0;
	while (y <= draw_start)
	{
		my_mlx_pixel_put(img, x, y, light_blue);
		y++;
	}
	while (y <= draw_end)
	{
		my_mlx_pixel_put(img, x, y, color);
		y++;
	}
	while (y <= screen_height)
	{
		my_mlx_pixel_put(img, x, y, gray);
		y++;
	}
}
void clear()
{
	int y = 0;
	while (y <= screen_height)
	{
		horizontal_line(y, 0, screen_width, 0x0000000, vars, &img);
		y++;
	}
}


int key_press(int keycode, t_player *player)
{

	if (keycode == arrow_up)
	{
		/* printf("%d\n", keycode); */
		if (worldMap[(int)(player->pos_x + player->dir_x * player->move_speed)][(int)(player->pos_y)] == false)
			player->pos_x += player->dir_x * player->move_speed;
		if (worldMap[(int)(player->pos_x)][(int)(player->pos_y + player->dir_y * player->move_speed)] == false)
			player->pos_y += player->dir_y * player->move_speed;
	}
	if (keycode == arrow_down)
	{
		if (worldMap[(int)(player->pos_x - player->dir_x * player->move_speed)][(int)(player->pos_y)] == false)
			player->pos_x -= player->dir_x * player->move_speed;
		if (worldMap[(int)player->pos_x][(int)(player->pos_y - player->dir_y * player->move_speed)] == false)
			player->pos_y -= player->dir_y * player->move_speed;
	}
	if (keycode == arrow_right)
	{
		double old_dir_x = player->dir_x;
		player->dir_x = player->dir_x * cos(-player->rot_speed) - player->dir_y * sin(-player->rot_speed);
		player->dir_y = old_dir_x * sin(-player->rot_speed) + player->dir_y * cos(-player->rot_speed);
		double old_plane_x = plane_x;
		plane_x = plane_x * cos(-player->rot_speed) - plane_y * sin(-player->rot_speed);
		plane_y = old_plane_x * sin(-player->rot_speed) + plane_y * cos(-player->rot_speed);
	}
	if (keycode == arrow_left)
	{
		//both camera direction and camera plane must be rotated
		double old_dir_x = player->dir_x;
		player->dir_x = player->dir_x * cos(player->rot_speed) - player->dir_y * sin(player->rot_speed);
		player->dir_y = old_dir_x * sin(player->rot_speed) + player->dir_y * cos(player->rot_speed);
		double old_plane_x = plane_x;
		plane_x = plane_x * cos(player->rot_speed) - plane_y * sin(player->rot_speed);
		plane_y = old_plane_x * sin(player->rot_speed) + plane_y * cos(player->rot_speed);
	}
	return 0;
}

int game_loop(t_player *player)
{
	for(int x = 0; x < screen_width; x++)
	{
		//calculate ray position and direction
		double camera_x = 2 * x / (double)screen_width - 1; //x-coordinate in camera space
		double ray_dir_x = player->dir_x + plane_x * camera_x;
		double ray_dir_y = player->dir_y + plane_y * camera_x;
		
		//which box of the map we're in
		int map_x = (int)player->pos_x;
		int map_y = (int)player->pos_y;

		//length of ray from current position to next x or y-side
		double side_dist_x;
		double side_dist_y;

		//length of ray from one x or y-side to next x or y-side
		double delta_dist_x = fabs(1.0 / ray_dir_x);
		double delta_dist_y = fabs(1.0 / ray_dir_y);
		double perp_wall_dist;

		//what direction to step in x or y-direction (either +1 or -1)
		int step_x;
		int step_y;

		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?

		//calculate step and initial sideDist
		if (ray_dir_x < 0)
		{
			step_x = -1;
			side_dist_x = (player->pos_x - map_x) * delta_dist_x;
		}
		else
		{
			step_x = 1;
			side_dist_x = (map_x + 1.0 - player->pos_x) * delta_dist_x;
		}
		if (ray_dir_y < 0)
		{
			step_y = -1;
			side_dist_y = (player->pos_y - map_y) * delta_dist_y;
		}
		else
		{
			step_y = 1;
			side_dist_y = (map_y + 1.0 - player->pos_y) * delta_dist_y;
		}
		
		/*perform DDA*/
		while (hit == 0)
		{
			/*jump to next map square, or in x_direction, or in y-direction*/
			if (side_dist_x < side_dist_y)
			{
				side_dist_x += delta_dist_x;
				map_x += step_x;
				side = 0;
			}
			else
			{
				side_dist_y += delta_dist_y;
				map_y += step_y;
				side = 1;
			}
			/*check if ray has hit a wall*/
			if (worldMap[map_x][map_y] > 0) hit = 1;
		}
		/*Calculate the distance projected on camera direction (Euclidean distance will give fisheye effect!)*/
		if (side == 0)
			perp_wall_dist = (map_x - player->pos_x + (1.0 - step_x) / 2) / ray_dir_x;
		else
			perp_wall_dist = (map_y - player->pos_y + (1.0 - step_y) / 2) / ray_dir_y;
		/* calculate line_height */
		int line_height = (int)(screen_height / perp_wall_dist);

		/*calculate the lowest and highest pixel fo fill in the current stripe*/
		int draw_start = -line_height / 2 + screen_height / 2;
		if (draw_start < 0) draw_start = 0;
		int draw_end = line_height / 2 + screen_height / 2;
		if (draw_end >= screen_height) draw_end = screen_height - 1;
		
		// choose wall color
		t_hex_color color;
		switch(worldMap[map_x][map_y])
		{
		case 1:  color = red;  break;
		case 2:  color = green;  break;
		case 3:  color = blue;   break;
		case 4:  color = white;  break;
		default: color = yellow; break;
		}
		
		// gives x and y different brightness
		if (side == 1) color = color / 2;

		vertical_line(x, draw_start, draw_end, color, vars, &img);
	}
	//Updates the screen.  Has to be called to view new pixels, but use only after
	//drawing the whole screen because it's slow.
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	// TODO: clear the screen with a recycled image using mlx_put_image_to_window
	/* clear(); */
	/* mlx_destroy_image(vars.mlx, img.img); */
	/* img.img = mlx_new_image(vars.mlx, screen_width, screen_height); */
	/* img.addr = (int *)mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian); */
	// speed modifiers
	player->move_speed = 0.2; //frame_time * 5.0; // the constant value is squares / second
	player->rot_speed = 0.03; //frame_time * 3.0; // the constant value is in radian / second

	return 0;
}


int		main(int argc, char *argv[argc])
{
	t_player player = {.pos_x = 22, .pos_y = 12, .dir_x = -1, .dir_y = 0, .move_speed = 1};
	plane_x = 0;
	plane_y = .66;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, screen_width, screen_height, "Cub3D");
	img.img = mlx_new_image(vars.mlx, screen_width, screen_height);
	img.addr = (int *)mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);

	mlx_loop_hook(vars.mlx, game_loop, &player);

	/* mlx_key_hook(vars.win, key_press, &player); */
	mlx_hook(vars.win, 2, 0, key_press, &player);

	mlx_loop(vars.mlx);

	return (0);
}
