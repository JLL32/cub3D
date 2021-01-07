#include "cub3D.h"

int		main(int argc, char *argv[argc])
{
	double pos_x = 22, pos_y = 12; /*x and y start position*/
	double dir_x = -1, dir_y = 0; /*initial direction vector*/
	double plane_x = 0, plane_y = 0.66; /*the 2D raycaster version of camera plane*/

	double time = 0; /*time of the current frame*/
	double time_old = 0; /*time of the previous frame*/

	void *mlx;
	void *mlx_win;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, screen_width, screen_height, "raycaster");
	mlx_loop(mlx);

	return (0);
}
