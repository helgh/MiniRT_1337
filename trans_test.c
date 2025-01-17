/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trans_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 11:22:46 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/01/16 18:31:11 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

int main()
{
	t_material	ma;
	t_ray		ray;
	t_tuple		normal_v;
	t_light		light;
	t_tuple		point;

	ma.diffuse = 0.9;
	ma.ambient = 0.1;
	ma.specular = 0.9;
	ma.shininess = 200.0;
	ma.color = set_color(1, 1, 1);
	ray.direction_v = create_tuple(0, 0, -1, 0);
	ray.origin_p = create_tuple(0, 0, 0, 1);
	normal_v = create_tuple(0, 0, -1, 0);
	light.color = set_color(1, 1, 1);
	light.cord = create_tuple(0, 0, 10, 1);
	point = create_tuple(0, 0, 0, 1);
	t_color	result = lighting(ma, light, ray, point, normal_v);
	printf("r: %f, g: %f, b: %f\n", result.r, result.g, result.b);
}
