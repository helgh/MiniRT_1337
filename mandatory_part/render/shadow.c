/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:51:57 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/03/20 00:39:22 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Minirt.h"

void	check_shadow(t_scene *scene, t_obj_draw *obj)
{
	t_ray		ray;
	t_tuple		v;
	t_tuple		direction;
	double		magn;

	if (!scene->light)
	{
		obj->shadow = true;
		return ;
	}
	v = op_tuple(scene->light->pos, obj->position, SUB);
	magn = magnitude(v);
	direction = normal(v);
	ray.origin_p = obj->position;
	ray.direction_v = direction;
	intersect_world(scene, &ray);
	if (scene->sect.exist == true && (magn - scene->sect.t) >= EPSILON)
		obj->shadow = true;
}
