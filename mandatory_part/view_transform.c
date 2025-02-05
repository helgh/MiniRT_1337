/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_transform.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 19:28:03 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/02/04 20:22:06 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

t_ray	ray_for_pixel(t_camera *camera, int pos_x, int pos_y)
{
	t_ray	ray;
	t_tuple	pixel;
	double	x_offset;
	double	y_offset;
	double	world_x;
	double	world_y;

	x_offset = (pos_x + 0.5) * camera->pixel_size;
	y_offset = (pos_y + 0.5) * camera->pixel_size;
	world_x = camera->half_width - x_offset;
	world_y = camera->half_height - y_offset;
	pixel = mult_mat_point(camera->inv_transform, point(world_x, world_y, -1.0));
	ray.origin_p = mult_mat_point(camera->inv_transform, point(0.0, 0.0, 0.0));
	ray.direction_v = normal(op_tuple(pixel, ray.origin_p, SUB));
	return (ray);
}

double	**view_transform(t_scene *scene, t_tuple from, t_tuple to, t_tuple up)
{
	t_tuple		forward;
	t_tuple		left;
	t_tuple		true_up;
	t_tmp_heap	*tmp;
	double	**orientation;

	tmp = scene->tmp_heap;
	forward = vector(to.x, to.y, to.z);
	left = cross_product(forward, normal(up));
	true_up = cross_product(left, forward);
	tmp->scal = identity_matrix(scene);
	tmp->scal[0][0] = left.x;
	tmp->scal[0][1] = left.y;
	tmp->scal[0][2] = left.z;
	tmp->scal[1][0] = true_up.x;
	tmp->scal[1][1] = true_up.y;
	tmp->scal[1][2] = true_up.z;
	tmp->scal[2][0] = -forward.x;
	tmp->scal[2][1] = -forward.y;
	tmp->scal[2][2] = -forward.z;
	tmp->trans = translation(scene, -from.x, -from.y, -from.z);
	orientation = mult_matrix(scene, tmp->scal, tmp->trans);
	scene->tmp_heap->trans = free_matrix(tmp->trans);
	scene->tmp_heap->scal = free_matrix(tmp->scal);
	return (orientation);
}
