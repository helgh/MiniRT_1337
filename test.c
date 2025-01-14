#include "Minirt.h"

int	handle_event(int keycode, t_mlx *m)
{
	(void) m;
	if (keycode == 53)
		exit(0);
	return (0);
}

double rgb_to_hex(double r, double g, double b) {
    // Ensure values are within valid range (0-255)
	double _r = r * 255.0;
	double _g = g * 255.0;
	double _b = b * 255.0;
    if (_r < 0) _r = 0; if (_r > 255) _r = 255;
    if (_g < 0) _g = 0; if (_g > 255) _g = 255;
    if (_b < 0) _b = 0; if (_b > 255) _b = 255;
	// printf("r = %d -- g = %d -- b = %d\n", _r, _g, _b);

    // Combine RGB values into a single hex value (opaque, alpha = FF)
    return ((u_int64_t)_r << 16 | (u_int64_t)_g << 8 | (u_int64_t)_b);
}

int main()
{
	// t_intersect	*inter;
	// t_sphere	sp;
	// t_ray		ray;
	// t_tuple		start;
	// t_tuple		dir;
	// t_tuple		cord;

	// cord.x = 500;
	// cord.y = 500;
	// cord.z = 0;
	// cord.w = 1;
	// sp.cord = cord;
	// start.x = 500;
	// start.y = 500;
	// start.z = 100;
	// start.w = 1;
	// dir.x = 250;
	// dir.y = 250;
	// dir.z = 0;
	// dir.w = 0;
	// ray.origin_p = start;
	// ray.direction_v = dir;
	// sp.radius = 50;
	// sp.trans = identity_matrix();
	// sp.trans = mult_matrix(mult_matrix(scaling(sp.radius, sp.radius, sp.radius, 1), translation(sp.cord.x, sp.cord.y, sp.cord.z, 1)), sp.trans);
	// inter = intersect_sphere(&sp, &ray);
	// printf("%.2f -- %.2f\n", inter->point_sec[0], inter->point_sec[1]);
	t_mlx	*m;
	t_ray	ray;
	t_sphere	sp;
	t_intersect	*intersect;

	sp.radius = 5;
	sp.cord.x = 0;
	sp.cord.y = 0;
	sp.cord.z = 0;
	sp.cord.w = 1;
	ray.origin_p.x = 0;
	ray.origin_p.y = 0;
	ray.origin_p.z = -20;
	ray.origin_p.w = 1;
	void	*mlx;
	void	*mlx_win;
	void	*mlx_img;
	m = malloc(sizeof(t_mlx));

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1000, 1000, "rendering sphere");
	mlx_img = mlx_new_image(mlx, 1000, 1000);
	m->pixels = mlx_get_data_addr(mlx_img, &m->bpp, &m->size_line, &m->endian);
	char *pix;
	int	y = 0;
	sp.trans = mult_matrix(translation(0, 0, 0, 1), scaling(30, 30, 1, 1));
	// printf("   %f ----\n", sp.trans[0][3]);
	// printf("   %f ----\n", sp.trans[1][3]);
	// printf("   %f ----\n", sp.trans[2][3]);
	// printf("   %f ----\n", sp.trans[3][3]);
	// sleep(10);
	// unsigned int hex_color = rgb_to_hex(1.0, 0.2, 1.0);  // For color (1.0, 0.2, 1.0)
	// printf("Hex color: 0x%X\n", hex_color);  // Output: 0xFF33FF
	// sleep(10);
	int pixel_size = 1;
	int half = 500;
	t_material ma;
	t_light	light;
	light.color = set_color(1, 1, 1);
	light.cord = create_tuple(-10, 10, -10, 1);
	light.brightness = 1.0;
	ma.color = set_color(1, 0.2, 1);
	t_tuple pos;
	t_tuple nor;
	ma.diffuse = 0.9;
	ma.ambient = 0.1;
	ma.specular = 0.9;
	ma.shininess = 200.0;
	while (++y < 1000)
	{
		int world_y = half - (pixel_size * y);
		int	x = 0;
		while (++x < 1000)
		{
			int world_x = -half + (pixel_size * x);
			ray.direction_v.x = (double) world_x;
			ray.direction_v.y = (double) world_y;
			ray.direction_v.z = 20;
			ray.direction_v = normal(ray.direction_v);
			intersect = intersect_sphere(&sp, &ray);
			// sleep(10);
			pix = m->pixels + (int)(y * m->size_line + x * (m->bpp / 8));
			if (intersect)
			{
				pos = cord_point_sec(ray, hit(intersect));
				nor = normal_at(sp, pos);
				ray.direction_v = oposite(ray.direction_v);
				ray.direction_v = normal(ray.direction_v);
				t_color	color = lighting(ma, light, ray, pos, nor);
				// printf("r = %f -- g = %f -- b = %f\n", color.r, color.g, color.b);
				*(int *)pix = rgb_to_hex(color.r, color.g, color.b);
				// printf("Hex color: 0x%X\n", *(int *)pix);
				// sleep(10);
				// *(int *)pix = 0xFF0000;
				// sleep (10);
			}
			else
				*(int *)pix = 0x000000;
		}
	}
	mlx_put_image_to_window(mlx, mlx_win, mlx_img, 0, 0);
	mlx_key_hook(mlx_win, &handle_event, &m);
	mlx_loop(mlx);

}
