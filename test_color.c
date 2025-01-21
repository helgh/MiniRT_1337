/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 13:06:00 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/01/19 13:45:19 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

int main()
{
	t_ray		ray;
	t_light		light;
	t_sphere	sp;
	t_material	ma;
	t_world		world;

	ray.origin_p = create_tuple(0, 0, 0.75, 1);
	// ray.origin_p = create_tuple(0, 0, 0, 1);
	ray.direction_v = create_tuple(0, 0, -1, 0);
	light.color = set_color(1, 1, 1);
	light.cord = create_tuple(-10, 10, -10, 1);
	// light.cord = create_tuple(0, 0.25, 0, 1);
	ma.ambient = 1.0;
	ma.diffuse = 0.9;
	ma.specular = 0.9;
	ma.shininess = 200;
	ma.color = set_color(0.8, 1.0, 0.6);
	// ma.color = set_color(1, 1, 1);
	sp.radius = 1;
	sp.id = 0;
	sp.cord = create_tuple(0, 0, 0, 1);
	sp.ma = ma;
	// sp.trans = scaling(0.5, 0.5, 0.5);
	sp.trans = identity_matrix();
	sp.inv_trans = inverse(sp.trans);
	sp.transpose_matrix = transpose(sp.trans);
	sp.transpose_inv_matrix = transpose(sp.inv_trans);
	world.light[0] = light;
	world.obj_count = 1;
	world.sp[0] = sp;
	t_color color = shad_hit(&world, &ray);
	printf("color: r = %f g = %f b = %f\n", color.r, color.g, color.b);
}
