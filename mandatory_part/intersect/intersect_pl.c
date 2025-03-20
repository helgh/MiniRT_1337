/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_pl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 15:30:22 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/03/20 00:36:02 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Minirt.h"

t_intersect	intersect_plane(t_scene *scene, t_plane *pl, t_ray *ray)
{
	t_intersect	sec;
	t_ray		new_ray;
	double		t;

	(void) scene;
	new_ray = transform_ray(ray, pl->inv_trans);
	if (fabs(new_ray.direction_v.y) < EPSILON)
		return (sec.exist = false, sec);
	t = -new_ray.origin_p.y / new_ray.direction_v.y;
	if (t < EPSILON)
		return (sec.exist = false, sec);
	sec.t = t;
	sec.pl = *pl;
	sec.type = PLANE;
	return (sec.exist = true, sec);
}
