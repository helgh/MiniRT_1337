/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:52:53 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/03/20 23:54:00 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Minirt.h"

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
		local_vec.y = 0;
	world_vec = mult_mat_point(obj.cy->transpose_inv_matrix, local_vec);
	world_vec.w = 0;
	return (normal(world_vec));
}

static t_tuple	normal_sp(t_obj_draw obj, t_tuple pos)
{
	t_tuple	obj_p;
	t_tuple	local_vec;
	t_tuple	world_vec;

	obj_p = mult_mat_point(obj.sp->inv_trans, pos);
	local_vec = obj_p;
	local_vec.w = 0.0;
	world_vec = mult_mat_point(obj.sp->transpose_inv_matrix, local_vec);
	world_vec.w = 0.0;
	return (normal(world_vec));
}

t_tuple	normal_at(t_obj_draw obj, t_tuple poin, int op)
{
	if (op == SPHERE)
		return (normal_sp(obj, poin));
	else if (op == PLANE)
		return (obj.pl->normal_v);
	return (normal_cy(obj, poin));
}

t_color	lighting(t_light *light, t_obj_draw *obj, t_am_light *am_light, \
	t_color col)
{
	t_color	ambient;
	t_color	difusse;
	t_tuple	light_v;
	double	light_normal;

	difusse = color(0.0, 0.0, 0.0);
	ambient = op_color(am_light->f_color, col, MULT);
	if (obj->shadow == true)
		return (ambient);
	light_v = normal(op_tuple(light->pos, obj->position, SUB));
	light_normal = dot_product(light_v, obj->normal_v);
	if (light_normal >= 0.0)
	{
		difusse = op_color(light->f_color, col, MULT);
		difusse = color_scal(difusse, light_normal, MULT);
	}
	return (op_color(ambient, difusse, ADD));
}
