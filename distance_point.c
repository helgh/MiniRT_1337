/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance_point.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 19:14:33 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/12/17 15:44:35 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

double	distance_point(t_tuple *p1, t_tuple *p2)
{
	double	distance;
	t_tuple	*sub;

	sub = subtract(p1, p2);
	distance = magnitude(sub);
	return (distance);
}

// int main ()
// {
	// t_tuple	*point = malloc(sizeof(t_tuple));
	// t_tuple	*vec = malloc(sizeof(t_tuple));

	// point->x = 2;
	// point->y = 3;
	// point->z = 4;
	// point->w = 1;
	// vec->x = 1;
	// vec->y = 0;
	// vec->z = 0;
	// vec->w = 1;
	// double	distance = distance_point(point, vec);
	// printf("%f\n", distance);
	// t_ray *ray = malloc(sizeof(t_ray));
	// ray->origin_p = malloc(sizeof(t_tuple));
	// ray->direction_v = malloc(sizeof(t_tuple));
	// ray->origin_p = point;
	// ray->direction_v = vec;
	// t_tuple	*new_point = position(ray, 0);
	// printf("x = %f -- y = %f -- z = %f\n", new_point->x, new_point->y, new_point->z);
	// new_point = position(ray, 1);
	// printf("x = %f -- y = %f -- z = %f\n", new_point->x, new_point->y, new_point->z);
	// new_point = position(ray, -1);
	// printf("x = %f -- y = %f -- z = %f\n", new_point->x, new_point->y, new_point->z);
	// new_point = position(ray, 2.5);
	// printf("x = %f -- y = %f -- z = %f\n", new_point->x, new_point->y, new_point->z);
// }
