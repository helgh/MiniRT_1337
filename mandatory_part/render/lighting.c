/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:52:53 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/03/03 15:03:48 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Minirt.h"

t_tuple	normal_at(t_obj_draw obj, t_tuple poin, int op)
{
	t_tuple	obj_p;
	t_tuple	world_vec;
	double	dis;

	if (op == SPHERE)
	{
		obj_p = mult_mat_point(obj.sp->inv_trans, poin);
		world_vec = mult_mat_point(obj.sp->transpose_inv_matrix, obj_p);
		world_vec.w = 0.0;
		return (normal(world_vec));
	}
	else if (op == PLANE)
		return (*obj.pl->normal_v);
	obj_p = mult_mat_point(obj.cy->inv_trans, poin);
	dis = (obj_p.x * obj_p.x) + (obj_p.z * obj_p.z);
	if (dis < 1.0 && obj_p.y > (obj.cy->max_min - EPSILON))
		return (vector(0.0, 1.0, 0.0));
	else if (dis < 1.0 && obj_p.y < -obj.cy->max_min + EPSILON)
		return (vector(0.0, -1.0, 0.0));
	obj_p.y = 0;
	world_vec = mult_mat_point(obj.cy->transpose_inv_matrix, obj_p);
	return (world_vec.w = 0, normal(world_vec));
}

t_color	lighting(t_light *light, t_obj_draw *obj, t_am_light *am_light)
{
	t_color	ambient;
	t_color	difusse;
	t_color	object;
	t_tuple	light_v;
	double	light_normal;

	if (obj->render == SPHERE)
		object = *obj->sp->color;
	else if (obj->render == PLANE)
		object = *obj->pl->color;
	else
		object = *obj->cy->color;
	difusse = color(0.0, 0.0, 0.0);
	ambient = op_color(*am_light->f_color, object, MULT);
	light_v = normal(op_tuple(*light->pos, obj->position, SUB));
	light_normal = dot_product(light_v, obj->normal_v);
	if (obj->shadow == true)
		return (ambient);
	if (light_normal >= 0.0)
	{
		difusse = op_color(*light->f_color, object, MULT);
		difusse = color_scal(difusse, light_normal, MULT);
	}
	return (op_color(ambient, difusse, ADD));
}
