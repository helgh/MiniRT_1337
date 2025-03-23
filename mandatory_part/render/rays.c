/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:06:05 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/03/23 00:35:52 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Minirt.h"

t_ray	transform_ray(t_ray *ray, double **a)
{
	t_ray	new_ray;

	new_ray.origin_p = mult_mat_point(a, ray->origin_p);
	new_ray.direction_v = mult_mat_point(a, ray->direction_v);
	return (new_ray);
}

t_ray	ray_for_pixel(t_camera *camera, int pos_x, int pos_y)
{
	t_ray	ray;
	t_tuple	pixel;
	double	x_offset;
	double	y_offset;
	double	world[2];

	x_offset = (pos_x + 0.5) * camera->pixel_size;
	y_offset = (pos_y + 0.5) * camera->pixel_size;
	world[0] = camera->half_width - x_offset;
	world[1] = camera->half_height - y_offset;
	pixel = mult_mat_point(camera->inv_transform, \
		point(world[0], world[1], -1.0));
	ray.origin_p = mult_mat_point(camera->inv_transform, point(0.0, 0.0, 0.0));
	ray.direction_v = normal(op_tuple(pixel, ray.origin_p, SUB));
	return (ray);
}

t_tuple	point_sec(t_ray cam, double t)
{
	t_tuple	direction;

	direction = tuple_scal(cam.direction_v, t, MULT);
	return (op_tuple(cam.origin_p, direction, ADD));
}
