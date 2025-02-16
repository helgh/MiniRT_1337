/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_pl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 15:30:22 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/02/16 19:00:54 by hael-ghd         ###   ########.fr       */
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
	sec = ft_malloc(scene, sizeof(t_intersect));
	sec->t = t;
	sec->type = PLANE;
	sec->id = pl->id;
	sec->next = NULL;
	return (sec);
}
