/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:28:58 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/01/11 20:12:29 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

int	count_size(double **a)
{
	int	i;

	i = -1;
	while (a[++i])
		;
	return (i);
}

t_ray	transform_ray(t_ray *ray, double **a)
{
	t_ray	new_ray;

	new_ray.origin_p = mult_mat_point(a, ray->origin_p);
	new_ray.direction_v = mult_mat_point(a, ray->direction_v);
	// printf("%f\n", new_ray.origin_p.x);
	// printf("%f\n", new_ray.origin_p.y);
	// printf("%f\n", new_ray.origin_p.z);
	// printf("%f\n", new_ray.origin_p.w);
	// printf("%f\n", new_ray.direction_v.x);
	// printf("%f\n", new_ray.direction_v.y);
	// printf("%f\n", new_ray.direction_v.z);
	// printf("%f\n", new_ray.direction_v.w);
	// sleep(10);
	// free_sub_matrix(a);
	return (new_ray);
}

double	**transform_sphere(t_sphere *sp, t_tuple *trans)
{
	double	**tr;
	double	**scal;

	tr = translation(trans->x, trans->y, trans->z, trans->w);
	scal = scaling(trans->x, trans->y, trans->z, trans->w);
	sp->trans = mult_matrix(tr, scal);
	return (sp->trans);
}
