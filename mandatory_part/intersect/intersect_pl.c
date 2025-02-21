/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_pl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 15:30:22 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/02/21 16:11:59 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Minirt.h"

t_intersect	*intersect_plane(t_scene *scene, t_plane *pl, t_ray *ray)
{
	t_intersect	*sec;
	t_ray		new_ray;
	double		t;

	new_ray = transform_ray(ray, pl->inv_trans);
	if (fabs(new_ray.direction_v.y) < EPSILON)
		return (NULL);
	t = -new_ray.origin_p.y / new_ray.direction_v.y;
	if (t < EPSILON)
		return (NULL);
	sec = malloc(sizeof(t_intersect));
	if (!sec)
		print_scene_err(scene, F_MALL);
	sec->t = t;
	sec->type = PLANE;
	sec->pl = pl;
	sec->next = NULL;
	return (sec);
}
