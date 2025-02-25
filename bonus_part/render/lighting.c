/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:52:53 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/02/24 21:06:07 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Minirt.h"

static t_color	_get_dif_spe(t_light light, t_tuple light_v, t_obj_draw *obj, \
	t_color col)
{
	t_tuple	ref;
	t_color	difusse;
	t_color	specular;
	double	light_normal;
	double	ref_dot_eye;

	light_normal = dot_product(light_v, obj->normal_v);
	if (light_normal >= 0.0)
	{
		specular = color(0.0, 0.0, 0.0);
		difusse = op_color(*light.f_color, col, MULT);
		difusse = color_scal(difusse, light_normal, MULT);
		ref = reflect(tuple_scal(light_v, -1, OPP), obj->normal_v);
		ref_dot_eye = dot_product(ref, obj->eye_v);
		if (ref_dot_eye > 0.0)
		{
			specular = color_scal(*light.f_color, \
				pow(ref_dot_eye, 200.0 * 0.7), MULT);
		}
		return (op_color(difusse, specular, ADD));
	}
	return (color(0.0, 0.0, 0.0));
}

static t_tuple normal_cylinder(t_obj_draw obj, t_tuple poin)
{
	t_tuple	obj_p;
	t_tuple	world_vec;
	double	dis;

	obj_p = mult_mat_point(obj.cy->inv_trans, poin);
	dis = (obj_p.x * obj_p.x) + (obj_p.z * obj_p.z);
	if (dis < 1 && obj_p.y >= obj.cy->max_min - EPSILON)
		return (vector(0.0, 1.0, 0.0));
	else if (dis < 1 && obj_p.y <= -obj.cy->max_min + EPSILON)
		return (vector(0.0, -1.0, 0.0));
	obj_p.y = 0;
	world_vec = mult_mat_point(obj.cy->transpose_inv_matrix, obj_p);
	return (world_vec.w = 0, normal(world_vec));
}

static t_tuple normal_cone(t_obj_draw obj, t_tuple poin)
{
	t_tuple	obj_p;
	t_tuple	world_vec;
	double	dis;
	double	y;

	obj_p = mult_mat_point(obj.cone->inv_trans, poin);
	dis = (obj_p.x * obj_p.x) + (obj_p.z * obj_p.z);
	if (dis < 1 && obj_p.y >= obj.cone->max_min - EPSILON)
		return (vector(0.0, 1.0, 0.0));
	else if (dis < 1 && obj_p.y <= -obj.cone->max_min + EPSILON)
		return (vector(0.0, -1.0, 0.0));
	y = sqrt(dis);
	if (obj_p.y > 0.0)
		y = -y;
	obj_p.y = y;
	world_vec = mult_mat_point(obj.cone->transpose_inv_matrix, obj_p);
	return (world_vec.w = 0, normal(world_vec));
}

t_tuple	normal_at(t_obj_draw obj, t_tuple poin, int op)
{
	t_tuple	obj_p;
	t_tuple	obj_n;
	t_tuple	world_vec;

	if (op == SPHERE)
	{
		obj_p = mult_mat_point(obj.sp->inv_trans, poin);
		obj_n = op_tuple(obj_p, point(0.0, 0.0, 0.0), SUB);
		if (obj.sp->flag_text)
			obj_n = _bump_mapping(obj, obj_p, obj_n);
		world_vec = mult_mat_point(obj.sp->transpose_inv_matrix, obj_n);
		world_vec.w = 0.0;
		return (normal(world_vec));
	}
	else if (op == CONE)
		return (normal_cone(obj, poin));
	else if (op == CYLINDER)
		return (normal_cylinder(obj, poin));
	return (*obj.pl->normal_v);
}

t_color	lighting(t_scene *scene, t_obj_draw *obj, t_am_light *am_light, \
	t_color col)
{
	t_color	ambient;
	t_color	dif_spe;
	t_tuple	light_v;
	t_light	*light;

	light = scene->light;
	dif_spe = color(0.0, 0.0, 0.0);
	ambient = op_color(*am_light->f_color, col, MULT);
	while (light)
	{
		if (!check_shadow(scene, obj, *light))
		{
			light_v = normal(op_tuple(*light->pos, obj->position, SUB));
			dif_spe = op_color(dif_spe, \
				_get_dif_spe(*light, light_v, obj, col), ADD);
		}
		light = light->next;
	}
	return (op_color(ambient, dif_spe, ADD));
}
