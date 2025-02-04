/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 16:09:12 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/02/04 18:45:59 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

double	discriminant_cy(t_ray *ray, double *arr)
{
	double	discriminant;

	arr[0] = pow(ray->direction_v.x, 2) + pow(ray->direction_v.z, 2);
	if (fabs(arr[0]) < EPSILON)
		return (-1);
	arr[1] = 2.0 * ray->origin_p.x * ray->direction_v.x;
	arr[1] += 2.0 * ray->origin_p.z * ray->direction_v.z;
	arr[2] = pow(ray->origin_p.x, 2) + pow(ray->origin_p.z, 2) - 1.0;
	discriminant = pow(arr[1], 2.0) - (4.0 * arr[0] * arr[2]);
	return (discriminant);
}

bool	check_cap(t_ray ray, double t)
{
	double	x;
	double	z;

	x = ray.origin_p.x + (t * ray.direction_v.x);
	z = ray.origin_p.z + (t * ray.direction_v.z);
	return ((x * x) + (z * z) <= 1.0);
}

void	check_cap_sect(t_intersect *sec, t_cylinder *cy, t_ray ray)
{
	double	t1;
	double	t2;

	ray.direction_v = normal(ray.direction_v);
	if (fabs(ray.direction_v.y) < EPSILON)
		;
	t1 = ((-cy->max_min - ray.origin_p.y) / ray.direction_v.y);
	t2 = ((cy->max_min - ray.origin_p.y) / ray.direction_v.y);
	if (check_cap(ray, t1))
	{
		if (sec->point_sec_1 == -INFINITY)
			sec->point_sec_1 = t1;
		else if (sec->point_sec_2 == -INFINITY)
			sec->point_sec_2 = t1;
	}
	if (check_cap(ray, t2))
	{
		if (sec->point_sec_1 == -INFINITY)
			sec->point_sec_1 = t2;
		else if (sec->point_sec_2 == -INFINITY)
			sec->point_sec_2 = t2;
	}
}

void	truncate_cylinder(t_cylinder *cy, t_ray ray, t_intersect *sec)
{
	double	y1;

	y1 = ray.origin_p.y + (sec->point_sec_1 * ray.direction_v.y);
	if (y1 < -cy->max_min || y1 > cy->max_min)
		sec->point_sec_1 = -INFINITY;
	y1 = ray.origin_p.y + (sec->point_sec_2 * ray.direction_v.y);
	if (y1 < -cy->max_min || y1 > cy->max_min)
		sec->point_sec_2 = -INFINITY;
}

t_intersect	*intersect_cylinder(t_scene *scene, t_cylinder *cy, t_ray *ray)
{
	t_intersect	*sec;
	t_ray		new_ray;
	double		dis;
	double		arr[3];

	new_ray = transform_ray(ray, cy->inv_trans);
	dis = discriminant_cy(&new_ray, arr);
	sec = ft_malloc(scene, sizeof(t_intersect), true);
	if (dis < 0)
		return (NULL);
	sec->point_sec_1 = (-(arr[1]) - sqrt(dis)) / (2.0 * arr[0]);
	sec->point_sec_2 = (-(arr[1]) + sqrt(dis)) / (2.0 * arr[0]);
	truncate_cylinder(cy, new_ray, sec);
	if (sec->point_sec_1 < EPSILON && sec->point_sec_2 < EPSILON)
		return (NULL);
	sec->type = CYLINDER;
	sec->id = cy->id;
	sec->next = NULL;
	// check_cap_sect(sec, cy, new_ray);
	choise_point(sec);
	return (sec);
}
