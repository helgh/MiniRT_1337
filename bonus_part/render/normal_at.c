/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_at.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 21:21:16 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/03/24 01:04:52 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Minirt_bonus.h"

static t_tuple	normal_cy(t_obj_draw obj, t_tuple pos)
{
	t_tuple	obj_p;
	t_tuple	local_vec;
	t_tuple	world_vec;
	double	dis;

	obj_p = mult_mat_point(obj.cy->inv_trans, pos);
	local_vec = obj_p;
	local_vec.w = 0.0;
	dis = (obj_p.x * obj_p.x) + (obj_p.z * obj_p.z);
	if (dis < 1.0 && obj_p.y > (obj.cy->max_min - EPSILON))
		local_vec = vector(0.0, 1.0, 0.0);
	else if (dis < 1.0 && obj_p.y < -obj.cy->max_min + EPSILON)
		local_vec = vector(0.0, -1.0, 0.0);
	else
	{
		if (obj.cy->path)
			local_vec = _bump_map_cylinder(obj, obj_p);
		local_vec.y = 0.0;
	}
	world_vec = mult_mat_point(obj.cy->transpose_inv_matrix, local_vec);
	world_vec.w = 0.0;
	return (normal(world_vec));
}

static t_tuple	normal_cone(t_obj_draw obj, t_tuple poin)
{
	t_tuple	obj_p;
	t_tuple	local_vec;
	t_tuple	world_vec;
	double	dis;
	double	y;

	obj_p = mult_mat_point(obj.cone->inv_trans, poin);
	dis = (obj_p.x * obj_p.x) + (obj_p.z * obj_p.z);
	y = sqrt(dis);
	local_vec = obj_p;
	local_vec.w = 0.0;
	if (dis < 1 && obj_p.y >= obj.cone->max_min - EPSILON)
		local_vec = vector(0.0, 1.0, 0.0);
	else if (dis < 1 && obj_p.y <= -obj.cone->max_min + EPSILON)
		local_vec = vector(0.0, -1.0, 0.0);
	else
	{
		if (obj_p.y > 0.0)
			y = -y;
		local_vec.y = y;
	}
	world_vec = mult_mat_point(obj.cone->transpose_inv_matrix, local_vec);
	return (world_vec.w = 0, normal(world_vec));
}

static t_tuple	normal_sp(t_obj_draw obj, t_tuple pos)
{
	t_tuple	obj_p;
	t_tuple	local_vec;
	t_tuple	world_vec;

	obj_p = mult_mat_point(obj.sp->inv_trans, pos);
	local_vec = obj_p;
	local_vec.w = 0.0;
	if (obj.sp->path)
		local_vec = _bump_map_sphere(obj, obj_p);
	world_vec = mult_mat_point(obj.sp->transpose_inv_matrix, local_vec);
	world_vec.w = 0.0;
	return (normal(world_vec));
}

t_tuple	normal_at(t_obj_draw obj, t_tuple poin, int op)
{
	if (op == SPHERE)
		return (normal_sp(obj, poin));
	else if (op == CYLINDER)
		return (normal_cy(obj, poin));
	else if (op == CONE)
		return (normal_cone(obj, poin));
	if (obj.pl->path)
	{
		obj.pl->normal_v = _bump_map_plane(obj, poin);
		obj.pl->normal_v = mult_mat_point(obj.pl->transpose_inv_matrix, \
			obj.pl->normal_v);
	}
	return (obj.pl->normal_v);
}
