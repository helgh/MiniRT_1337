/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 18:48:59 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/11/08 15:54:21 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

double	discriminant(t_sphere *sp, t_ray *ray)
{
	t_tuple	*sp_to_origin;
	double	a;
	double	b;
	double	c;
	double	discriminant;

	//sp_to_origin = subtract(ray->origin_p, sp->cord);
	a = dot_product(ray->direction_v, ray->direction_v);
	b = 2 * dot_product(ray->direction_v, ray->origin_p);
	c = dot_product(ray->origin_p, ray->origin_p) - pow(sp->radius, 2);
	discriminant = pow(b, 2) - (4 * a * c);
	return (discriminant);
}

t_intersect	*intersect_sphere(t_sphere *sp, t_ray *ray, int flag)
{
	t_intersect	*sec;
	t_ray		*new_ray;
	double		dis;
	double		b;
	double		a;

	new_ray = transform_ray(ray, inverse(transform_sphere(sp, sp->cord, flag)));
	dis = discriminant(sp, new_ray);
	if (dis < 0)
		return (free(new_ray), NULL);
	sec = malloc(sizeof(t_intersect));
	if (!sec)
		return (free(new_ray), NULL);
	sec->point_sec = malloc(sizeof(double) * 2);
	if (!sec->point_sec)
		return (free(new_ray), free(sec), NULL);
	a = dot_product(new_ray->direction_v, new_ray->direction_v);
	b = 2 * dot_product(new_ray->direction_v, subtract(new_ray->origin_p, sp->cord));
	sec->nbr_sec = 2;
	sec->point_sec[0] = (-(b) - sqrt(dis)) / (2 * a);
	sec->point_sec[1] = (-(b) + sqrt(dis)) / (2 * a);
	sec->object = sp;
	sec->next = NULL;
	free (new_ray);
	return (sec);
}

