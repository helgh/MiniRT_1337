/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_transformation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 14:58:16 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/01/22 13:15:19 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

t_ray	ray_for_pixel(t_camera camera, double pos_x, double pos_y)
{
	t_ray	ray;
	t_tuple	pixel;
	double	x_offset;
	double	y_offset;
	double	world_x;
	double	world_y;

	x_offset = (pos_x + 0.5) * camera.pixel_size;
	y_offset = (pos_y + 0.5) * camera.pixel_size;
	world_x = camera.half_width - x_offset;
	world_y = camera.half_height - y_offset;
	pixel = mult_mat_point(camera.inv_transform, create_tuple(world_x, world_y, -1, 1));
	ray.origin_p = mult_mat_point(camera.inv_transform, create_tuple(0, 0, 0, 1));
	ray.direction_v = normal(op_tuple(pixel, ray.origin_p, '-', 1));
	return (ray);
}


double	**view_transform(t_tuple from, t_tuple to, t_tuple up)
{
	t_tuple	forward;
	t_tuple	left;
	t_tuple	true_up;
	double	**trans;
	double	**view;
	double	**orientation;

	forward = normal(op_tuple(to, from, '-', 1));
	left = cross_product(forward, normal(up));
	true_up = cross_product(left, forward);
	view = identity_matrix();
	view[0][0] = left.x;
	view[0][1] = left.y;
	view[0][2] = left.z;
	view[1][0] = true_up.x;
	view[1][1] = true_up.y;
	view[1][2] = true_up.z;
	view[2][0] = -forward.x;
	view[2][1] = -forward.y;
	view[2][2] = -forward.z;
	trans = translation(-from.x, -from.y, -from.z);
	orientation = mult_matrix(view, trans);
	return (free(view), free(trans), orientation);
}

t_camera	_camera(double fov, double width, double height)
{
	t_camera	cam;
	t_tuple		to;
	t_tuple		up;

	to = create_tuple(0, 1, 0, 1);
	up = create_tuple(0, 1, 0, 0);
	cam.hor_size = width;
	cam.ver_size = height;
	cam.FOV = fov;
	cam.cord = create_tuple(0, 1.5, -5, 1);
	cam.transform = view_transform(cam.cord, to, up);
	cam.inv_transform = inverse(cam.transform);
	cam.aspect = cam.hor_size / cam.ver_size;
	if (cam.aspect >= 1.0)
	{
		cam.half_width = tan(fov / 2);
		cam.half_height = cam.half_width / cam.aspect;
	}
	else
	{
		cam.half_height = tan(fov / 2);
		cam.half_width = cam.half_height * cam.aspect;
	}
	cam.pixel_size = (cam.half_width * 2) / cam.hor_size;
	return (cam);
}