/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_sp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 17:07:52 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/02/16 19:00:59 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Minirt.h"

static double	discriminant(t_ray *ray, double *arr)
{
	double	discriminant;

	arr[0] = dot_product(ray->direction_v, ray->direction_v);
	arr[1] = 2.0 * dot_product(ray->direction_v, ray->origin_p);
	arr[2] = dot_product(ray->origin_p, ray->origin_p) - 1.0;
	discriminant = pow(arr[1], 2.0) - (4.0 * arr[0] * arr[2]);
	return (discriminant);
}

t_intersect	*intersect_sphere(t_scene *scene, t_sphere *sp, t_ray *ray)
{
	t_intersect	*sec;
	t_ray		new_ray;
	double		dis;
	double		arr[3];

	new_ray = transform_ray(ray, sp->inv_trans);
	dis = discriminant(&new_ray, arr);
	if (dis < 0)
		return (NULL);
	sec = ft_malloc(scene, sizeof(t_intersect));
	sec->type = SPHERE;
	sec->id = sp->id;
	sec->next = NULL;
	sec->point_sec_1 = (-(arr[1]) - sqrt(dis)) / (2.0 * arr[0]);
	sec->point_sec_2 = (-(arr[1]) + sqrt(dis)) / (2.0 * arr[0]);
	if (sec->point_sec_1 < EPSILON && sec->point_sec_2 < EPSILON)
		return (NULL);
	choise_point(sec);
	return (sec);
}
