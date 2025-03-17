/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:52:53 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/03/17 21:20:50 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Minirt_bonus.h"

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
