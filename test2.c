#include <mlx.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#define WIDTH 100
#define HEIGHT 100

typedef struct s_tuple {
    float x;
    float y;
    float z;
    float w;
} t_tuple;

typedef struct s_ray {
    t_tuple origin_p;
    t_tuple direction_v;
} t_ray;

typedef struct s_sphere {
    t_tuple center;
    float radius;
} t_sphere;

typedef struct s_light {
    t_tuple position;
    t_tuple intensity;
} t_light;

typedef struct s_mlx {
    void *mlx;
    void *window;
    void *image;
    char *pixels;
    int bpp;
    int size_line;
    int endian;
} t_mlx;

// Dot product of two vectors
float dot(t_tuple a, t_tuple b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

// Vector subtraction
t_tuple subtract(t_tuple a, t_tuple b) {
    t_tuple result;
    result.x = a.x - b.x;
    result.y = a.y - b.y;
    result.z = a.z - b.z;
    result.w = 1;
    return result;
}

// Vector addition
t_tuple add(t_tuple a, t_tuple b) {
    t_tuple result;
    result.x = a.x + b.x;
    result.y = a.y + b.y;
    result.z = a.z + b.z;
    result.w = 1;
    return result;
}

// Vector multiplication by scalar
t_tuple multiply_scalar(t_tuple v, float scalar) {
    t_tuple result;
    result.x = v.x * scalar;
    result.y = v.y * scalar;
    result.z = v.z * scalar;
    result.w = 1;
    return result;
}

// Ray-Sphere intersection calculation
int intersect_ray_sphere(t_ray *ray, t_sphere *sphere, float *t1, float *t2) {
    t_tuple oc = subtract(ray->origin_p, sphere->center);
    float a = dot(ray->direction_v, ray->direction_v);
    float b = 2.0f * dot(oc, ray->direction_v);
    float c = dot(oc, oc) - (sphere->radius * sphere->radius);
    float discriminant = b * b - 4.0f * a * c;

    if (discriminant < 0) {
        return 0;  // No intersection
    }

    *t1 = (-b - sqrt(discriminant)) / (2.0f * a);
    *t2 = (-b + sqrt(discriminant)) / (2.0f * a);
    return 1;  // Intersection found
}

// Check if the point is in shadow
int is_in_shadow(t_tuple point, t_light *light, t_sphere *sphere) {
    t_ray shadow_ray;
    float t1, t2;

    shadow_ray.origin_p = point;
    shadow_ray.direction_v = subtract(light->position, point);

    // Normalize the direction of the shadow ray
    float length = sqrt(dot(shadow_ray.direction_v, shadow_ray.direction_v));
    shadow_ray.direction_v = multiply_scalar(shadow_ray.direction_v, 1.0f / length);

    // Check if the shadow ray intersects the sphere
    if (intersect_ray_sphere(&shadow_ray, sphere, &t1, &t2)) {
        return 1;  // Point is in shadow
    }
    return 0;  // Point is not in shadow
}

// Set pixel color at (x, y) position on the image
void set_pixel(t_mlx *m, int x, int y, int color) {
    char *pixel = m->pixels + (y * m->size_line + x * (m->bpp / 8));
    *(int *)pixel = color;
}

// Main function to set up the scene and trace rays
int main() {
    t_mlx m;
    t_ray ray;
    t_sphere sphere;
    t_light light;
    float t1, t2;
    int x, y;

    // Set up the sphere (center at (0, 0, 0), radius 1)
    sphere.center.x = 0;
    sphere.center.y = 0;
    sphere.center.z = 0;
    sphere.radius = 1;

    // Set up the light source (position at (0, 10, -10))
    light.position.x = 0;
    light.position.y = 10;
    light.position.z = -10;
    light.intensity.x = 1.0f;
    light.intensity.y = 1.0f;
    light.intensity.z = 1.0f;

    // Set up the ray (camera at (0, 0, -5), looking straight ahead)
    ray.origin_p.x = 0;
    ray.origin_p.y = 0;
    ray.origin_p.z = -5;
    ray.origin_p.w = 1;
    ray.direction_v.x = 0;
    ray.direction_v.y = 0;
    ray.direction_v.z = 1;
    ray.direction_v.w = 0;

    // Initialize the MLX
    m.mlx = mlx_init();
    m.window = mlx_new_window(m.mlx, WIDTH, HEIGHT, "Ray Tracing with Shadows");
    m.image = mlx_new_image(m.mlx, WIDTH, HEIGHT);
    m.pixels = mlx_get_data_addr(m.image, &m.bpp, &m.size_line, &m.endian);

    // Wall properties
    float wall_z = 10;
    float wall_size = 7.0f;
    int canvas_pixels = 100;
    float pixel_size = wall_size / canvas_pixels;
    float half = wall_size / 2;

    // Main rendering loop
    for (y = 0; y < canvas_pixels; y++) {
        for (x = 0; x < canvas_pixels; x++) {
            // Compute the world y coordinate
            float world_y = half - pixel_size * y;

            // Compute the world x coordinate
            float world_x = -half + pixel_size * x;

            // Describe the point on the wall that the ray will target
            t_tuple position = {world_x, world_y, wall_z, 1};

            // Cast the ray from the origin to the point on the wall
            ray.direction_v = subtract(position, ray.origin_p);
            float length = sqrt(dot(ray.direction_v, ray.direction_v));
            ray.direction_v = multiply_scalar(ray.direction_v, 1.0f / length);  // Normalize the direction

            // Check if the ray intersects the sphere
            if (intersect_ray_sphere(&ray, &sphere, &t1, &t2)) {
                // Compute the intersection point
                t_tuple intersection_point = add(ray.origin_p, multiply_scalar(ray.direction_v, t1));

                // Check if the point is in shadow
                if (is_in_shadow(intersection_point, &light, &sphere)) {
                    // If point is in shadow, color it dark red (0x8B0000)
                    set_pixel(&m, x, y, 0x8B0000);
                }
            //  else {
                //     // Otherwise, color it red (0xFF0000)
                //     set_pixel(&m, x, y, 0xFFFF00);
                // }
            } else {
                // If no intersection, color the pixel black (0x000000)
                set_pixel(&m, x, y, 0xFFFFFF);
            }
        }
    }

    // Display the image on the window
    mlx_put_image_to_window(m.mlx, m.window, m.image, 0, 0);

    // Handle events (e.g., key press)
    // mlx_key_hook(m.window, &handle_event, &m);
    mlx_loop(m.mlx);

    return 0;
}
