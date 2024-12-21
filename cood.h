#ifndef COOD_H
#define COOD_H

#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define WIDTH 900
#define HEIGHT 550

typedef struct s_point {
    float x, y, z;
} Point;

typedef struct s_vector {
    float x, y, z;
} Vector;

typedef struct s_projectile {
    Point position;
    Vector velocity;
} Projectile;

typedef struct s_environment {
    Vector gravity;
    Vector wind;
} Environment;

typedef struct s_mlx {
    void *mlx;
    void *win;
    void *img;
    int *data;
} MLX;

// Function prototypes
Vector add(Vector v1, Vector v2);
Vector scale(Vector v, float scalar);
float dot(Vector v1, Vector v2);
Vector normalize(Vector v);
Projectile create_projectile(Point position, Vector velocity);
Environment create_environment(Vector gravity, Vector wind);
Projectile tick(Environment env, Projectile proj);
void print_position(Projectile proj);
void draw_pixel(MLX *mlx, int x, int y, int color);
int handle_close(void *param);

#endif