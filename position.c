/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   position.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 22:09:05 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/11/01 19:23:10 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

t_tuple	*position(t_ray *ray, double t)
{
	t_tuple	*new_point;
	t_tuple	vec;

	new_point = malloc(sizeof(t_tuple));
	if (!new_point)
		return (NULL);
	vec.x = t * ray->direction_v->x;
	vec.y = t * ray->direction_v->y;
	vec.z = t * ray->direction_v->z;
	new_point->x = ray->origin_p->x + vec.x;
	new_point->y = ray->origin_p->y + vec.y;
	new_point->z = ray->origin_p->z + vec.z;
	new_point->w = 1;
	return (new_point);
}
// int main ()
// {
// 	t_tuple	*point = malloc(sizeof(t_tuple));
// 	t_tuple	*vec = malloc(sizeof(t_tuple));

// 	point->x = 2;
// 	point->y = 3;
// 	point->z = 4;
// 	point->w = 1;
// 	vec->x = 1;
// 	vec->y = 0;
// 	vec->z = 0;
// 	vec->w = 0;
// 	t_ray *ray = malloc(sizeof(t_ray));
// 	ray->origin_p = malloc(sizeof(t_tuple));
// 	ray->direction_v = malloc(sizeof(t_tuple));
// 	ray->origin_p = point;
// 	ray->direction_v = vec;
// 	t_tuple	*new_point = position(ray, 0);
// 	printf("x = %f -- y = %f -- z = %f\n", new_point->x, new_point->y, new_point->z);
// 	new_point = position(ray, 1);
// 	printf("x = %f -- y = %f -- z = %f\n", new_point->x, new_point->y, new_point->z);
// 	new_point = position(ray, -1);
// 	printf("x = %f -- y = %f -- z = %f\n", new_point->x, new_point->y, new_point->z);
// 	new_point = position(ray, 2.5);
// 	printf("x = %f -- y = %f -- z = %f\n", new_point->x, new_point->y, new_point->z);
// }
