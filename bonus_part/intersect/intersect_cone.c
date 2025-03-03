/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cone.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:53:26 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/03/03 15:17:46 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Minirt.h"

static double	discriminant_cone(t_ray *ray, double *arr)
{
	double	discriminant;

	arr[0] = pow(ray->direction_v.x, 2) - pow(ray->direction_v.y, 2) + \
		pow(ray->direction_v.z, 2);
	arr[1] = 2.0 * ((ray->origin_p.x * ray->direction_v.x) - \
		(ray->origin_p.y * ray->direction_v.y) + \
		(ray->origin_p.z * ray->direction_v.z));
	arr[2] = pow(ray->origin_p.x, 2) - pow(ray->origin_p.y, 2) + \
		pow(ray->origin_p.z, 2);
	discriminant = pow(arr[1], 2.0) - (4.0 * arr[0] * arr[2]);
	return (discriminant);
}

static void	truncate_cone(t_cone *cone, t_ray ray, t_intersect *sec)
{
	double	y1;

	y1 = ray.origin_p.y + (sec->point_sec_1 * ray.direction_v.y);
	if (y1 < -cone->max_min || y1 > cone->max_min)
		sec->point_sec_1 = -1;
	y1 = ray.origin_p.y + (sec->point_sec_2 * ray.direction_v.y);
	if (y1 < -cone->max_min || y1 > cone->max_min)
		sec->point_sec_2 = -1;
}

t_intersect	*intersect_cone(t_scene *scene, t_cone *cone, t_ray *ray)
{
	t_intersect	*sec;
	t_ray		new_ray;
	double		dis;
	double		arr[3];

	new_ray = transform_ray(ray, cone->inv_trans);
	sec = ft_malloc(scene, sizeof(t_intersect), true);
	dis = discriminant_cone(&new_ray, arr);
	sec->type = CONE;
	sec->next = NULL;
	// if (arr[0] == 0.0)
	// {
	// 	printf("here\n");
	// 	if (arr[1] <= 0.0)
	// 		return (NULL);
	// 	return (sec->t = -arr[2] / (2.0 * arr[1]), sec);
	// }
	if (dis < 0)
		return (NULL);
	sec->point_sec_1 = (-(arr[1]) - sqrt(dis)) / (2.0 * arr[0]);
	sec->point_sec_2 = (-(arr[1]) + sqrt(dis)) / (2.0 * arr[0]);
	truncate_cone(cone, new_ray, sec);
	if (sec->point_sec_1 < EPSILON && sec->point_sec_2 < EPSILON)
		return (NULL);
	choise_point(sec);
	return (sec);
}
