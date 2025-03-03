/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 16:09:12 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/03/03 15:44:01 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Minirt.h"

static double	discriminant_cy(t_ray *ray, double *arr)
{
	double	discriminant;

	arr[0] = pow(ray->direction_v.x, 2) + pow(ray->direction_v.z, 2);
	if (arr[0] <= 0.0)
		return (-1);
	arr[1] = 2.0 * ((ray->origin_p.x * ray->direction_v.x) + \
		(ray->origin_p.z * ray->direction_v.z));
	arr[2] = pow(ray->origin_p.x, 2) + pow(ray->origin_p.z, 2) - 1.0;
	discriminant = pow(arr[1], 2.0) - (4.0 * arr[0] * arr[2]);
	return (discriminant);
}

static void	truncate_cylinder(t_cylinder *cy, t_ray ray, t_intersect *sec)
{
	double	y1;

	y1 = ray.origin_p.y + (sec->point_sec_1 * ray.direction_v.y);
	if (y1 < -cy->max_min || y1 > cy->max_min)
		sec->point_sec_1 = -1;
	y1 = ray.origin_p.y + (sec->point_sec_2 * ray.direction_v.y);
	if (y1 < -cy->max_min || y1 > cy->max_min)
		sec->point_sec_2 = -1;
}

t_intersect	*intersect_cylinder(t_scene *scene, t_cylinder *cy, t_ray *ray)
{
	t_intersect	*sec;
	t_ray		new_ray;
	double		dis;
	double		arr[3];

	new_ray = transform_ray(ray, cy->inv_trans);
	sec = ft_malloc(scene, sizeof(t_intersect));
	dis = discriminant_cy(&new_ray, arr);
	if (dis < 0.0)
		return (NULL);
	sec->point_sec_1 = (-(arr[1]) - sqrt(dis)) / (2.0 * arr[0]);
	sec->point_sec_2 = (-(arr[1]) + sqrt(dis)) / (2.0 * arr[0]);
	truncate_cylinder(cy, new_ray, sec);
	if (sec->point_sec_1 < EPSILON && sec->point_sec_2 < EPSILON)
		return (NULL);
	sec->type = CYLINDER;
	sec->cy = cy;
	sec->next = NULL;
	choise_point(sec);
	return (sec);
}
