#include "Minirt.h"

int	handle_event(int keycode, t_mlx *m)
{
	(void) m;
	if (keycode == 53)
		exit(0);
	return (0);
}

double rgb_to_hex(double r, double g, double b)
{
	double min;
	double max;

	max = 1.0;
	min = 0.0;
    if (r < min) r = min; if (r > max) r = max;
    if (g < min) g = min; if (g > max) g = max;
    if (b < min) b = min; if (b > max) b = max;
	r *= 255.0;
	g *= 255.0;
	b *= 255.0;
    return ((u_int64_t)r << 16 | (u_int64_t)g << 8 | (u_int64_t)b);
	// t_color color = set_color(r, g, b);
	// return(color);
}

int main()
{
	t_mlx	*m;
	// t_ray		ray;
	t_light		light;
	t_sphere	sp;
	t_sphere	left_wall;
	t_sphere	right_wall;
	t_sphere	midlle;
	t_sphere	right;
	t_sphere	left;
	t_material	ma[6];
	t_world		world;
	t_camera	camera;

	for (int i = 0; i < 6; i++)
	{
		ma[i].ambient = 0.1;
		ma[i].diffuse = 0.9;
		ma[i].specular = 0;
		ma[i].shininess = 200;
		ma[i].color = set_color(1, 0.9, 0.9);
	}
	sp.id = 0;
	sp.cord = create_tuple(0, 0, 0, 1);
	sp.radius = 1;
	sp.trans = scaling(10, 0.01, 10);
	sp.inv_trans = inverse(sp.trans);
	sp.transpose_matrix = transpose(sp.trans);
	sp.transpose_inv_matrix = transpose(sp.inv_trans);
	sp.ma = ma[0];

	// left_wall = sp;
	left_wall.cord = create_tuple(0, 0, 0, 1);
	left_wall.radius = 1;
	left_wall.id = 1;
	left_wall.trans = mult_matrix(rotation(M_PI / 2, 'x'), scaling(10, 0.01, 10));
	left_wall.trans = mult_matrix(rotation(-(M_PI / 4), 'y'), left_wall.trans);
	left_wall.trans = mult_matrix(translation(0, 0, 5), left_wall.trans);
	left_wall.inv_trans = inverse(left_wall.trans);
	left_wall.transpose_matrix = transpose(left_wall.trans);
	left_wall.transpose_inv_matrix = transpose(left_wall.inv_trans);
	left_wall.ma = ma[1];

	// right_wall = sp;
	right_wall.cord = create_tuple(0, 0, 0, 1);
	right_wall.id = 2;
	right_wall.radius = 1;
	right_wall.trans = mult_matrix(rotation(M_PI / 2, 'x'), scaling(10, 0.01, 10));
	right_wall.trans = mult_matrix(rotation(M_PI / 4, 'y'), right_wall.trans);
	right_wall.trans = mult_matrix(translation(0, 0, 5), right_wall.trans);
	right_wall.inv_trans = inverse(right_wall.trans);
	right_wall.transpose_matrix = transpose(right_wall.trans);
	right_wall.transpose_inv_matrix = transpose(right_wall.inv_trans);
	right_wall.ma = ma[2];

	// midlle = sp;
	midlle.cord = create_tuple(0, 0, 0, 1);
	midlle.id = 3;
	midlle.radius = 1;
	midlle.trans = translation(-0.5, 1, 0.5);
	midlle.inv_trans = inverse(midlle.trans);
	midlle.transpose_matrix = transpose(midlle.trans);
	midlle.transpose_inv_matrix = transpose(midlle.inv_trans);
	midlle.ma = ma[3];
	midlle.ma.color = set_color(0.1, 1, 0.5);
	midlle.ma.diffuse = 0.7;
	midlle.ma.specular = 0.3;

	// right = sp;
	right.cord = create_tuple(0, 0, 0, 1);
	right.id = 4;
	right.radius = 1;
	right.trans = mult_matrix(translation(1.5, 0.5, -0.5), scaling(0.5, 0.5, 0.5));
	right.inv_trans = inverse(right.trans);
	right.transpose_matrix = transpose(right.trans);
	right.transpose_inv_matrix = transpose(right.inv_trans);
	right.ma = ma[4];
	right.ma.color = set_color(0.5, 1, 0.1);
	right.ma.diffuse = 0.7;
	right.ma.specular = 0.3;

	// left = sp;
	left.cord = create_tuple(0, 0, 0, 1);
	left.id = 5;
	left.radius = 1;
	left.trans = mult_matrix(translation(-1.5, 0.33, -0.75), scaling(0.33, 0.33, 0.33));
	left.inv_trans = inverse(left.trans);
	left.transpose_matrix = transpose(left.trans);
	left.transpose_inv_matrix = transpose(left.inv_trans);
	left.ma = ma[5];
	left.ma.color = set_color(1, 0.8, 0.1);
	left.ma.diffuse = 0.7;
	left.ma.specular = 0.3;

	light.color = set_color(1, 1, 1);
	light.cord = create_tuple(-10, 10, -10, 1);

	camera = _camera(M_PI / 3, 900, 500);

	world.light[0] = light;
	world.obj_count = 6;
	world.sp_count = 6;
	world.sp[0] = sp;
	world.sp[1] = left_wall;
	world.sp[2] = right_wall;
	world.sp[3] = midlle;
	world.sp[4] = right;
	world.sp[5] = left;
	// world.obj_count = 3;
	// world.sp_count = 3;
	// midlle.id = 0;
	// right.id = 1;
	// left.id = 2;
	// world.sp[0] = midlle;
	// world.sp[1] = right;
	// world.sp[2] = left;

	void	*mlx;
	void	*mlx_win;
	void	*mlx_img;
	m = malloc(sizeof(t_mlx));

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 900, 500, "rendering sphere");
	mlx_img = mlx_new_image(mlx, 900, 500);
	m->pixels = mlx_get_data_addr(mlx_img, &m->bpp, &m->size_line, &m->endian);
	int pix;
	int	y = -1;
	while (++y < camera.ver_size)
	{
		int	x = -1;
		while (++x < camera.hor_size)
		{
			t_ray	rays = ray_for_pixel(camera, x, y);
			pix = (y * m->size_line + x * (m->bpp / 8));
			t_color	color = shad_hit(&world, &rays);
			double col = rgb_to_hex(color.r, color.g, color.b);
			*(int *)(m->pixels + pix) = col;
			// *(m->pixels + pix) = col.r;
			// *(m->pixels + pix + 1) = col.g;
			// *(m->pixels + pix + 2) = col.b;
		}
	}
	mlx_put_image_to_window(mlx, mlx_win, mlx_img, 0, 0);
	mlx_key_hook(mlx_win, &handle_event, &m);
	mlx_loop(mlx);
}
