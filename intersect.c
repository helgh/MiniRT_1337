/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 18:48:59 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/11/05 19:06:24 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

double	discriminant(t_sphere *sp, t_ray *ray)
{
	t_axis	*sp_to_origin;
	double	a;
	double	b;
	double	c;
	double	discriminant;

	sp_to_origin = subtract(ray->origin_p, sp->cord);
	a = dot_product(ray->direction_v, ray->direction_v);
	b = 2 * dot_product(ray->direction_v, sp_to_origin);
	c = dot_product(sp_to_origin, sp_to_origin);
	discriminant = power(b, 2) - (4 * a * c);
	return (discriminant);
}

t_intersect	*intersect_sphere(t_sphere *sp, t_ray *ray)
{
	double	dis;

	dis = discriminant(sp, ray);
	if (dis < 0)
		return (NULL);
	
}