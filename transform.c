/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:28:58 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/11/07 17:35:27 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

t_ray	*transform_ray(t_ray *ray, double **a, int flag)
{
	t_ray	*new_ray;
	t_ray	*tmp;

	tmp->origin_p->x = a[0][3];
	tmp->origin_p->y = a[1][3];
	tmp->origin_p->z = a[2][3];
	tmp->origin_p->w = a[3][3];
	new_ray->direction_v = ray->direction_v;
	if (flag == TRANSLATING)
		new_ray->origin_p = addition(ray->origin_p, tmp);
	else if (flag == SCALING)
	{
		new_ray = malloc(sizeof(t_ray));
		if (!new_ray)
			return (NULL);
		new_ray->origin_p->x = tmp->origin_p->x * ray->origin_p->x;
		new_ray->origin_p->y = tmp->origin_p->y * ray->origin_p->y;
		new_ray->origin_p->z = tmp->origin_p->z * ray->origin_p->z;
		new_ray->origin_p->w = tmp->origin_p->w * ray->origin_p->w;
		new_ray->direction_v->x = tmp->origin_p->x * ray->direction_v->x;
		new_ray->direction_v->y = tmp->origin_p->y * ray->direction_v->y;
		new_ray->direction_v->z = tmp->origin_p->z * ray->direction_v->z;
		new_ray->direction_v->w = tmp->origin_p->w * ray->direction_v->w;
	}
	return (new_ray);
}
