#include "cood.h"

void draw_pixel(MLX *mlx, int x, int y, int color) {
    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
        mlx->data[y * WIDTH + x] = color;
    }
}

int handle_close(void *param) {
    mlx_destroy_window(((MLX *)param)->mlx, ((MLX *)param)->win);
    exit(0);
    return (0);
}

Vector add(Vector v1, Vector v2) {
    Vector result = { v1.x + v2.x, v1.y + v2.y, v1.z + v2.z };
    return result;
}

Vector scale(Vector v, float scalar) {
    Vector result = { v.x * scalar, v.y * scalar, v.z * scalar };
    return result;
}

float dot(Vector v1, Vector v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

Vector normalize(Vector v) {
    float length = sqrt(dot(v, v));
    return scale(v, 1.0f / length);
}

Projectile create_projectile(Point position, Vector velocity) {
    Projectile p = { position, velocity };
    return p;
}

Environment create_environment(Vector gravity, Vector wind) {
    Environment e = { gravity, wind };
    return e;
}

Projectile tick(Environment env, Projectile proj) {
    proj.position = add(proj.position, proj.velocity);
    proj.velocity = add(proj.velocity, add(env.gravity, env.wind));
    return proj;
}

void print_position(Projectile proj) {
    printf("Position: (%.2f, %.2f, %.2f)\n", proj.position.x, proj.position.y, proj.position.z);
}


int main() {
    MLX mlx;
    Projectile p;
    Environment e;
    int tick_count = 0;

    // Initialize MLX window
    mlx.mlx = mlx_init();
    mlx.win = mlx_new_window(mlx.mlx, WIDTH, HEIGHT, "Projectile Simulation");
    mlx.img = mlx_new_image(mlx.mlx, WIDTH, HEIGHT);
    mlx.data = (int *)mlx_get_data_addr(mlx.img, &(int){32}, &(int){WIDTH * 4}, &(int){0});

    // Create projectile and environment
    Point start_position = {0.0f, 1.0f, 0.0f};  // Position (0, 1, 0)
    Vector start_velocity = normalize((Vector){1.0f, 1.8f, 0.0f});
    start_velocity = scale(start_velocity, 11.25);  // Scale the velocity for visible motion
    p = create_projectile(start_position, start_velocity);
    Vector gravity = {0.0f, -0.1f, 0.0f};
    Vector wind = {-0.01f, 0.0f, 0.0f};
    e = create_environment(gravity, wind);

    // Main simulation loop
    while (p.position.y > 0) {
        // Clear the image (fill with black)
        for (int i = 0; i < WIDTH * HEIGHT; i++) {
            mlx.data[i] = 0x000000; // Black color
        }

        // Draw the projectile at its new position (convert to pixel coordinates)
        int x = (int)(p.position.x);
        int y = (int)(HEIGHT - p.position.y);  // Invert y-axis for window coordinates
        draw_pixel(&mlx, x, y, 0xFFFFFF); // Draw in white color

        // Update the projectile for the next tick
        p = tick(e, p);

        // Update the window with the new image
        mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.img, 0, 0);
        mlx_clear_window(mlx.mlx, mlx.win);

        // Delay to slow down the simulation and make it visible
        usleep(10000);  // Sleep for 10 milliseconds

        tick_count++;  // Increment tick counter
    }

    // Final message
    printf("The projectile hit the ground after %d ticks.\n", tick_count);

    // Event loop
    mlx_hook(mlx.win, 17, 0, handle_close, &mlx); // Close the window when clicked
    mlx_loop(mlx.mlx);

    return 0;
}

