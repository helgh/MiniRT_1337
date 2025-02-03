/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 12:45:05 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/01/28 14:06:08 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

t_color	set_color(double r, double g, double b)
{
	t_color	color;

	color.r = r;
	color.g = g;
	color.b = b;
	return (color);
}

t_tuple	point_sec(t_ray cam, double t)
{
	return (op_tuple(cam.origin_p, op_tuple(cam.direction_v, cam.direction_v, 0, t), '+', 1));
}

t_color	lighting(t_material m, t_light light, t_tuple eye_v, t_tuple point, t_tuple normal_v, t_obj_draw sp)
{
	t_color	difusse;
	t_color	specular;
	t_color	effe_color;
	t_color	ambient;
	t_tuple	light_v;
	double	light_normal;
	double	ref_dot_eye;

	difusse = set_color(0, 0, 0);
	specular = set_color(0, 0, 0);
	effe_color = op_color(m.color, light.color, '*', 1);
	light_v = normal(op_tuple(light.cord, point, '-', 1));
	ambient = op_color(effe_color, effe_color, 0, m.ambient);
	light_normal = dot_product(light_v, normal_v);
	if (sp.shadow)
		return (ambient);
	if (light_normal >= EPSILON)
	{	
		difusse = op_color(effe_color, effe_color, 0, light_normal);
		t_tuple new_ref = reflect(oposite(light_v), normal_v);
		ref_dot_eye = dot_product(new_ref, eye_v);
		if (ref_dot_eye > EPSILON)
		{
			double factor = pow(ref_dot_eye, m.shininess) * m.specular;
			specular = op_color(light.color, light.color, 0, factor);
		}
	}
	t_color result = op_color(ambient, difusse, '+', 1);
	result = op_color(result, specular, '+', 1);
	return (result);
}
