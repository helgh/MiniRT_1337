#include "Minirt.h"

int	handle_event(int keycode, t_mlx *m)
{
	(void) m;
	if (keycode == 53)
		exit(0);
	return (0);
}

t_color rgb_to_hex(double r, double g, double b)
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
    // return ((u_int64_t)r << 16 | (u_int64_t)g << 8 | (u_int64_t)b);
	t_color color = set_color(r, g, b);
	return(color);
}

int main()
{
	t_mlx	*m;
	t_ray	ray;
	t_sphere	sp;
	t_intersect	*intersect;

	sp.radius = 1;
	sp.cord.x = 0;
	sp.cord.y = 0;
	sp.cord.z = 0;
	sp.cord.w = 1;
	ray.origin_p.x = 0;
	ray.origin_p.y = 0;
	ray.origin_p.z = -5;
	ray.origin_p.w = 1;
	void	*mlx;
	void	*mlx_win;
	void	*mlx_img;
	m = malloc(sizeof(t_mlx));

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 800, 800, "rendering sphere");
	mlx_img = mlx_new_image(mlx, 800, 800);
	m->pixels = mlx_get_data_addr(mlx_img, &m->bpp, &m->size_line, &m->endian);
	int pix;
	int	y = -1;
	double wall_size = 7.0;
	double wall_z = 10.0;
	double pixel_size = wall_size / 800.0;
	double half = wall_size / 2.0;
	sp.trans = translation(0, 0, 0);
	t_light	light;
	light.color = set_color(1, 1, 1);
	light.cord = create_tuple(-10, 10, -10, 1);
	light.brightness = 0.8;
	t_tuple nor;
	t_tuple pos;
	t_material ma;
	ma.color = set_color(1, 0.2, 1);
	ma.ambient = 0.1;
	ma.diffuse = 0.9;
	ma.specular = 0.9;
	ma.shininess = 32.0;
	while (++y < 800)
	{
		double world_y = half - (pixel_size * y);
		int	x = -1;
		while (++x < 800)
		{
			double world_x = -half + (pixel_size * x);
			ray.direction_v = normal(create_tuple(world_x, world_y, wall_z, 0));
			intersect = intersect_sphere(&sp, &ray);
			pix = (y * m->size_line + x * (m->bpp / 8));
			if (intersect->hit)
			{
				pos = point_sec(ray, hit(intersect));
				nor = normal_at(sp, pos);
				ray.direction_v = oposite(ray.direction_v);
				ray.direction_v = normal(ray.direction_v);
				t_color	color = lighting(ma, light, ray, pos, nor);
				t_color col = rgb_to_hex(color.r, color.g, color.b);
				*(m->pixels + pix) = col.r;
				*(m->pixels + pix + 1) = col.g;
				*(m->pixels + pix + 2) = col.b;
			}
			else
				*(int *)(m->pixels + pix) = 0X000000;
		}
	}
	mlx_put_image_to_window(mlx, mlx_win, mlx_img, 0, 0);
	mlx_key_hook(mlx_win, &handle_event, &m);
	mlx_loop(mlx);
}
