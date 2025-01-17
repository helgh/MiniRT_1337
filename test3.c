#include <mlx.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

// Structures
typedef struct {
    double x, y, z;
} t_vector;

typedef struct {
    double r, g, b;
} t_color;

typedef struct {
    t_vector origin;
    t_vector direction;
} t_ray;

typedef struct {
    t_color color;
    double ambient;
    double diffuse;
    double specular;
    double shininess;
} t_material;

typedef struct {
    t_vector position;
    t_color color;
    double intensity;
} t_light;

typedef struct {
    t_vector center;
    double radius;
    t_material material;
} t_sphere;

typedef struct {
    void *mlx;
    void *win;
    void *img;
    char *addr;
    int bpp;
    int line_len;
    int endian;
} t_mlx;

// Function prototypes
t_vector vector(double x, double y, double z);
t_vector normalize(t_vector v);
double dot(t_vector a, t_vector b);
t_vector subtract(t_vector a, t_vector b);
t_color color(double r, double g, double b);
t_color lighting(t_material m, t_light light, t_vector point, t_vector eyev, t_vector normalv);
void put_pixel(t_mlx *mlx, int x, int y, t_color color);
void render(t_mlx *mlx, t_sphere sphere, t_light light, int width, int height);

// Vector utility functions
t_vector vector(double x, double y, double z) {
    t_vector v = {x, y, z};
    return v;
}

t_vector normalize(t_vector v) {
    double magnitude = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    return vector(v.x / magnitude, v.y / magnitude, v.z / magnitude);
}

double dot(t_vector a, t_vector b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

t_vector subtract(t_vector a, t_vector b) {
    return vector(a.x - b.x, a.y - b.y, a.z - b.z);
}

// Color utility functions
t_color color(double r, double g, double b) {
    t_color c = {r, g, b};
    return c;
}

// Lighting calculation

t_color lighting(t_material m, t_light light, t_vector point, t_vector eyev, t_vector normalv) {
    t_color effective_color = color(m.color.r * light.color.r, m.color.g * light.color.g, m.color.b * light.color.b);
    t_color ambient = color(effective_color.r * m.ambient, effective_color.g * m.ambient, effective_color.b * m.ambient);

    t_vector lightv = normalize(subtract(light.position, point));
    double light_dot_normal = dot(lightv, normalv);

    t_color diffuse = {0, 0, 0};
    t_color specular = {0, 0, 0};

    if (light_dot_normal >= 0) {
        diffuse = color(
            effective_color.r * m.diffuse * light_dot_normal,
            effective_color.g * m.diffuse * light_dot_normal,
            effective_color.b * m.diffuse * light_dot_normal
        );

        t_vector reflectv = subtract(vector(normalv.x * 2 * light_dot_normal, normalv.y * 2 * light_dot_normal, normalv.z * 2 * light_dot_normal), lightv);
        double reflect_dot_eye = dot(reflectv, eyev);

        if (reflect_dot_eye > 0) {
            double factor = pow(reflect_dot_eye, m.shininess);
            specular = color(
                light.color.r * m.specular * factor,
                light.color.g * m.specular * factor,
                light.color.b * m.specular * factor
            );
        }
    }

    return color(
        ambient.r + diffuse.r + specular.r,
        ambient.g + diffuse.g + specular.g,
        ambient.b + diffuse.b + specular.b
    );
}

// Pixel drawing function
void put_pixel(t_mlx *mlx, int x, int y, t_color color) {
    if (x < 0 || x >= 800 || y < 0 || y >= 800)
        return;
	double min;
	double max;

	max = 1.0;
	min = 0.0;
    int pixel = (y * mlx->line_len + x * (mlx->bpp / 8));
	if (color.r < min) color.r = 0; if (color.r > max) color.r = 1;
    if (color.g < min) color.g = 0; if (color.g > max) color.g = 1;
    if (color.b < min) color.b = 0; if (color.b > max) color.b = 1;
    mlx->addr[pixel] = (int)(color.b * 255);
    mlx->addr[pixel + 1] = (int)(color.g * 255);
    mlx->addr[pixel + 2] = (int)(color.r * 255);
}

// Rendering function
void render(t_mlx *mlx, t_sphere sphere, t_light light, int width, int height) {
    t_vector eye = vector(0, 0, -5); // Camera position
    double wall_size = 7.0;
    double wall_z = 10.0;
    double pixel_size = wall_size / width;
    double half = wall_size / 2.0;

    for (int y = 0; y < height; y++) {
        double world_y = half - pixel_size * y;
        for (int x = 0; x < width; x++) {
            double world_x = -half + pixel_size * x;
            t_vector position = vector(world_x, world_y, wall_z);

            t_ray ray = {eye, normalize(subtract(position, eye))};

            // Check for intersection with the sphere
            t_vector sphere_to_ray = subtract(ray.origin, sphere.center);
            double a = dot(ray.direction, ray.direction);
            double b = 2 * dot(ray.direction, sphere_to_ray);
            double c = dot(sphere_to_ray, sphere_to_ray) - sphere.radius * sphere.radius;

            double discriminant = b * b - 4 * a * c;

            if (discriminant >= 0) {
                double t = (-b - sqrt(discriminant)) / (2 * a);
                t_vector point = vector(
                    ray.origin.x + ray.direction.x * t,
                    ray.origin.y + ray.direction.y * t,
                    ray.origin.z + ray.direction.z * t
                );

                t_vector normalv = normalize(subtract(point, sphere.center));
                t_vector eyev = vector(-ray.direction.x, -ray.direction.y, -ray.direction.z);

                t_color color = lighting(sphere.material, light, point, eyev, normalv);
                put_pixel(mlx, x, y, color);
            }
        }
    }
}

// Main function
int main() {
    t_mlx mlx;

    mlx.mlx = mlx_init();
    mlx.win = mlx_new_window(mlx.mlx, 800, 800, "Sphere Renderer");
    mlx.img = mlx_new_image(mlx.mlx, 800, 800);
    mlx.addr = mlx_get_data_addr(mlx.img, &mlx.bpp, &mlx.line_len, &mlx.endian);

    t_material material = {color(1, 0.2, 1), 0.1, 0.9, 0.9, 200};
    t_sphere sphere = {vector(0, 0, 10), 1.0, material};
    t_light light = {vector(-10, 10, -10), color(1, 1, 1), 0.8};

    render(&mlx, sphere, light, 800, 800);

    mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.img, 0, 0);
    mlx_loop(mlx.mlx);

    return 0;
}
