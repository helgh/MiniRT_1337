#include "Minirt.h"
# include <mlx.h>

#define WIDTH 1200
#define HEIGHT 800
#define COLOR 0xffffff

int main()
{

	int	bpp = 0;
	int	s = 0;
	int	end = 0;
	int	w = 600;
	int	h = 400;
	void *mlx = mlx_init();
	if (!mlx)
		return (1);
	void *mlx_w = mlx_new_window(mlx, WIDTH, HEIGHT, "clock");
	if (!mlx_w)
		return (1);
	void *mlx_i = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!mlx_i)
		return (1);
	char *addr = mlx_get_data_addr(mlx_i, &bpp, &s, &end);
	char *pixel;
	for (int i = 0; i < 12; i++)
	{
		pixel = addr + (h * s + w * (bpp / 8));
		*(int *)pixel = COLOR;
	}
	mlx_put_image_to_window(mlx, mlx_w, mlx_i, 0, 0);
	mlx_loop(mlx);
	// char *pixels = map->addr + (int)(y * map->s + x * (map->bpp / 8));
	// *(int *) pixels = map->b_go->color;
}
