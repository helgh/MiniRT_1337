/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 16:09:12 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/02/03 19:45:56 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

double	discriminant_cy(t_ray *ray, double *arr)
{
	double	discriminant;

	arr[0] = pow(ray->direction_v.x, 2) + pow(ray->direction_v.z, 2);
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

	x = pow (ray.origin_p.x + (t * ray.direction_v.x), 2);
	z = pow (ray.origin_p.z + (t * ray.direction_v.z), 2);
	return (x + z <= 1.0);
}

t_intersect	*check_cap_sect(t_intersect *sec, t_cylinder *cy, t_ray ray)
{
	double	t1;
	double	t2;

	if (ray.direction_v.y == 0)
		return (NULL);
	t1 = ((-(cy->height / 2) - ray.origin_p.y) / ray.direction_v.y);
	t2 = (((cy->height / 2) - ray.origin_p.y) / ray.direction_v.y);
	if (check_cap(ray, t1))
		return (sec->t = t1, sec);
	else if (check_cap(ray, t2))
		return (sec->t = t2, sec);
	return (NULL);
}

t_intersect	*intersect_cylinder(t_scene *scene, t_cylinder *cy, t_ray *ray)
{
	t_intersect	*sec;
	t_ray		new_ray;
	double		dis;
	double		arr[3];
	double		y1;

	new_ray = transform_ray(ray, cy->inv_trans);
	dis = discriminant_cy(&new_ray, arr);
	if (arr[0] < EPSILON || dis < 0)
		return (NULL);
	sec = ft_malloc(scene, sizeof(t_intersect), true);
	sec->type = CYLINDER;
	sec->id = cy->id;
	sec->next = NULL;
	sec->point_sec_1 = (-(arr[1]) - sqrt(dis)) / (2.0 * arr[0]);
	sec->point_sec_2 = (-(arr[1]) + sqrt(dis)) / (2.0 * arr[0]);
	if (sec->point_sec_1 < EPSILON && sec->point_sec_2 < EPSILON)
		return (NULL);
	choise_point(sec);
	y1 = new_ray.origin_p.y + sec->t * new_ray.direction_v.y;
	if (y1 < -(cy->height / 2.0) || y1 > (cy->height / 2.0))
		return (check_cap_sect(sec, cy, new_ray));
	return (sec);
}
