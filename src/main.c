#include "cub3D.h"

typedef struct  s_data {
    void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
}               t_data;

void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

int		main(int argc, char *argv[argc])
{
	double pos_x = 22, pos_y = 12; /*x and y start position*/
	double dir_x = -1, dir_y = 0; /*initial direction vector*/
	double plane_x = 0, plane_y = 0.66; /*the 2D raycaster version of camera plane*/

	double time = 0; /*time of the current frame*/
	double time_old = 0; /*time of the previous frame*/

	void *mlx;
	void *mlx_win;
	t_data  img;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, screen_width, screen_height, "Hello world!");
	img.img = mlx_new_image(mlx, screen_width, screen_height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								 &img.endian);
	my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);

	for(int x = 0; x < screen_width; x++) {
		//calculate ray position and direction
		double camera_x = 2 * x / (double)screen_width - 1; //x-coordinate in camera space
		double ray_dir_x = dir_x + plane_x * camera_x;
		double ray_dir_y = dir_y + plane_y * camera_x;
		my_mlx_pixel_put(&img, ray_dir_x, ray_dir_y, 0x00FF0000);
		mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
		
		//which box of the map we're in
		int map_x = (int)pos_x;
		int map_y = (int)pos_y;

		//length of ray from current position to next x or y-side
		double side_dist_x;
		double side_dist_y;

		//length of ray from one x or y-side to next x or y-side
		double delta_dist_x = abs(1 / (int)ray_dir_x);
		double delta_dist_y = abs(1 / (int)ray_dir_y);
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
			side_dist_x = (pos_x - map_x) * delta_dist_x;
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
	}

    mlx_loop(mlx);

	return (0);
}
