/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_sp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 17:07:52 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/01/24 18:57:41 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

t_ray	transform_ray(t_ray *ray, double **a)
{
	t_ray	new_ray;
	new_ray.origin_p = mult_mat_point(a, ray->origin_p);
	new_ray.direction_v = mult_mat_point(a, ray->direction_v);
	return (new_ray);
}

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

t_intersect	*intersect_sphere(t_scene *scene, t_sphere *sp, t_ray *ray)
{
	t_intersect	*sec;
	t_ray		new_ray;
	t_tuple		tuple;
	double		dis;
	double		b;
	double		a;

	new_ray = transform_ray(ray, sp->inv_trans);
	dis = discriminant(sp, &new_ray);
	if (dis < 0)
		return (NULL);
	sec = ft_malloc(scene, sizeof(t_intersect), true);
	sec->type = SPHERE;
	sec->id = sp->id;
	sec->next = NULL;
	a = dot_product(new_ray.direction_v, new_ray.direction_v);
	tuple = op_tuple(new_ray.origin_p, sp->pos, '-', 1);
	b = 2 * dot_product(new_ray.direction_v, tuple);
	sec->point_sec[0] = (-(b) - sqrt(dis)) / (2 * a);
	sec->point_sec[1] = (-(b) + sqrt(dis)) / (2 * a);
	if (sec->point_sec[0] < EPSILON && sec->point_sec[1] < EPSILON)
		return (NULL);
	return (sec);
}
