/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 18:48:59 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/01/10 19:36:53 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

double	discriminant(t_sphere *sp, t_ray *ray)
{
	double	a;
	double	b;
	double	c;
	double	discriminant;

	a = dot_product(ray->direction_v, ray->direction_v);
	b = 2 * dot_product(ray->direction_v, ray->origin_p);
	c = dot_product(ray->origin_p, ray->origin_p) - pow(sp->radius, 2);
	discriminant = pow(b, 2) - (4 * a * c);
	return (discriminant);
}

t_intersect	*intersect_sphere(t_sphere *sp, t_ray *ray)
{
	t_intersect	*sec;
	t_ray		new_ray;
	t_tuple		tuple;
	double		dis;
	double		b;
	double		a;

	new_ray = transform_ray(ray, inverse(sp->trans));
	dis = discriminant(sp, &new_ray);
	if (dis < 0)
		return (NULL);
	sec = malloc(sizeof(t_intersect));
	if (!sec)
		return (NULL);
	sec->point_sec = malloc(sizeof(double) * 2);
	if (!sec->point_sec)
		return (free(sec), NULL);
	a = dot_product(new_ray.direction_v, new_ray.direction_v);
	tuple = subtract(new_ray.origin_p, sp->cord);
	b = 2 * dot_product(new_ray.direction_v, tuple);
	sec->nbr_sec = 2;
	sec->point_sec[0] = (-(b) - sqrt(dis)) / (2 * a);
	sec->point_sec[1] = (-(b) + sqrt(dis)) / (2 * a);
	sec->object = sp;
	sec->next = NULL;
	return (sec);
}
