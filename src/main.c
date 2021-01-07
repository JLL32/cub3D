#include "cub3D.h"

int		main(int argc, char *argv[argc])
{
	double posX = 22, posY = 12; /*x and y start position*/
	double dirX = -1, dirY = 0; /*initial direction vector*/
	double planeX = 0, planeY = 0.66; /*the 2D raycaster version of camera plane*/

	double time = 0; /*time of the current frame*/
	double oldTime = 0; /*time of the previous frame*/

	void *mlx;
	void *mlx_win;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, screenWidth, screenHeight, "raycaster");
	mlx_loop(mlx);

	return (0);
}
