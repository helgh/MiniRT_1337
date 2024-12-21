/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_x.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 16:10:44 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/12/20 19:08:27 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

double	**rotate_x(double angle)
{
	double	**rot;

	rot = identity_matrix();
	rot[1][1] = cos(angle);
	rot[1][2] = -1 * sin(angle);
	rot[2][1] = sin(angle);
	rot[2][2] = cos(angle);
	return (rot);
}

double	**rotate_y(double angle)
{
	double	**rot;

	rot = identity_matrix();
	rot[0][0] = cos(angle);
	rot[0][2] = sin(angle);
	rot[2][0] = -1 * sin(angle);
	rot[2][2] = cos(angle);
	return (rot);
}
double	**rotate_z(double angle)
{
	double	**rot;

	rot = identity_matrix();
	rot[1][1] = cos(angle);
	rot[0][0] = cos(angle);
	rot[1][0] = sin(angle);
	rot[0][1] = -1 * sin(angle);
	return (rot);
}
int main()
{
	double	**tr;
	t_tuple	*point;
	t_tuple	*new_point;
	// void	*mlx = mlx_init();
	// void	*window = mlx_new_window(mlx, 1000, 800, "ray tracing");
	// void	*img = mlx_new_image(mlx, 500, 500);
	// mlx_put_image_to_window(mlx, window, img, 200, 400);
	// mlx_loop(mlx);
	tr = rotate_y(degree_to_rad(90));
	// tr = inverse(tr);
	point->x = 0;
	point->y = 0;
	point->z = 1;
	point->w = 1;
	new_point = mult_mat_point(tr, point);
	printf("x = %.2f\n", new_point->x);
	printf("y = %.2f\n", new_point->y);
	printf("z = %.2f\n", new_point->z);
	printf("w = %.2f\n", new_point->w);
}
