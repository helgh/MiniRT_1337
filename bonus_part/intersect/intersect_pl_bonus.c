/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_pl_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 15:30:22 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/03/05 18:22:45 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Minirt_bonus.h"

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
	sec->next = NULL;
	return (sec);
}
