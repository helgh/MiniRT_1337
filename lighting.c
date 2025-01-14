/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 12:45:05 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/01/14 12:24:51 by hael-ghd         ###   ########.fr       */
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

t_tuple	cord_point_sec(t_ray cam, double t)
{
	return (addition(cam.origin_p, mult_by_scalar(cam.direction_v, t)));
}
t_color get_rgb(double color)
{
	t_color col = set_color(0,0,0);
	col.r = ((u_int64_t)color >> 16) & 255;
	col.g = ((u_int64_t)color >> 8) & 255;
	col.b = ((u_int64_t)color) & 255;
	return (col);
}
t_color	lighting(t_material m, t_light light, t_ray eye, t_tuple point, t_tuple vec)
{
	t_color	difusse;
	t_color	specular;
	t_color	effe_color;
	t_color	ambient;
	t_tuple	light_v;
	double	light_normal;
	double	reflect_dot_eye;

	effe_color.r = m.color.r * light.color.r * light.brightness;
	effe_color.g = m.color.g * light.color.g * light.brightness;
	effe_color.b = m.color.b * light.color.b * light.brightness;
	light_v = subtract(light.cord, point);
	light_v = normal(light_v);
	ambient.r = effe_color.r * m.ambient;
	ambient.g = effe_color.g * m.ambient;
	ambient.b = effe_color.b * m.ambient;
	light_normal = dot_product(light_v, vec);
	if (light_normal < 0)
	{
		difusse = set_color(0, 0, 0);
		specular = set_color(0, 0, 0);
	}
	else
	{
		
		difusse.r = effe_color.r * m.diffuse * light_normal;
		difusse.g = effe_color.g * m.diffuse * light_normal;
		difusse.b = effe_color.b * m.diffuse * light_normal;
		t_tuple	ref_v;
		ref_v = reflect(oposite(light_v), vec);
		reflect_dot_eye = dot_product(ref_v, eye.direction_v);
		if (reflect_dot_eye <= 0)
			specular = set_color(0, 0, 0);
		else
		{
			double factor = pow(reflect_dot_eye, m.shininess);
			double r = light.brightness * m.specular * factor;
			specular = get_rgb(r);
		}
	}
	t_color final_color;

	final_color.r = specular.r + difusse.r + ambient.r;
	final_color.g = specular.g + difusse.g + ambient.g;
	final_color.b = specular.b + difusse.b + ambient.b;
	return (final_color);
}
