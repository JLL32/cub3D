#include "cub3D.h"

typedef struct  s_vars {
	void        *mlx;
	void        *win;
}               t_vars;

typedef struct  s_data {
	void        *img;
	char        *addr;
	int         bits_per_pixel;
	int         line_length;
	int         endian;
}               t_data;

typedef int t_hex_color;

enum colors {
	red		= 0x00FF000,
	maroon	= 0x0800000,
	yellow	= 0x0FFFF00,
	olive	= 0x0808000,
	blue	= 0x00000FF,
} colors;


void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char    *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void vertical_line(int x, int draw_start, int draw_end, t_hex_color color, t_vars vars, t_data *img)
{
	int y = draw_start;
	while (y <= draw_end)
	{
		my_mlx_pixel_put(img, x, y, color);
		y++;
	}
	mlx_put_image_to_window(vars.mlx, vars.win, img->img, 0, 0);
	
}


int		main(int argc, char *argv[argc])
{
	double pos_x = 22, pos_y = 12; /*x and y start position*/
	double dir_x = -1, dir_y = 0; /*initial direction vector*/
	double plane_x = 0, plane_y = 0.66; /*the 2D raycaster version of camera plane*/

	double time = 0; /*time of the current frame*/
	double time_old = 0; /*time of the previous frame*/

	t_data  img;

	t_vars vars;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, screen_width, screen_height, "Cub3D");
	img.img = mlx_new_image(vars.mlx, screen_width, screen_height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								 &img.endian);

	my_mlx_pixel_put(&img, 4, 5, maroon);
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 4, 5);

	/* vertical_line(100, 5, 80, yellow, vars, &img); */

	for(int x = 0; x < screen_width; x++)
	{
		//calculate ray position and direction
		double camera_x = 2 * x / (double)screen_width - 1; //x-coordinate in camera space
		double ray_dir_x = dir_x + plane_x * camera_x;
		double ray_dir_y = dir_y + plane_y * camera_x;
		
		//which box of the map we're in
		int map_x = pos_x;
		int map_y = pos_y;

		//length of ray from current position to next x or y-side
		double side_dist_x;
		double side_dist_y;

		//length of ray from one x or y-side to next x or y-side
		double delta_dist_x = (ray_dir_y == 0) ? 0 : ((ray_dir_x == 0) ? 1 : abs((int)(1 / ray_dir_x)));
		double delta_dist_y = (ray_dir_x == 0) ? 0 : ((ray_dir_y == 0) ? 1 : abs((int)(1 / ray_dir_y)));
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
			side_dist_x = (pos_x- map_x) * delta_dist_x;
		}
		else
		{
			step_x = 1;
			side_dist_x = (map_x + 1.0 - pos_x) * delta_dist_x;
		}
		if (ray_dir_y < 0)
		{
			step_y = -1;
			side_dist_y = (pos_y - map_y) * delta_dist_y;
		}
		else
		{
			step_y = 1;
			side_dist_y = (map_y + 1.0 - pos_y) * delta_dist_y;
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
			if (worldMap[map_x][map_x] > 0) hit = 1;
		}
		/*Calculate the distance projected on camera direction (Euclidean distance will give fisheye effect!)*/
		if (side == 0)
			perp_wall_dist = (map_x - pos_x + (1.0 - step_x) / 2) / ray_dir_x;
		else
			perp_wall_dist = (map_y - pos_y + (1.0 - step_y) / 2) / ray_dir_y;
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
		case 2:  color = olive;  break;
		case 3:  color = blue;   break;
		case 4:  color = maroon;  break;
		default: color = yellow; break;
		}

		if (side == 1) color = color / 2;

		vertical_line(x, draw_start, draw_end, color, vars, &img);
	}


	mlx_loop(vars.mlx);

	return (0);
}
