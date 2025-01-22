/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:28:58 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/01/22 14:40:14 by hael-ghd         ###   ########.fr       */
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
	return (new_ray);
}

double	**transform_sphere(t_sphere *sp, t_tuple *trans)
{
	double	**tr;
	double	**scal;

	tr = translation(trans->x, trans->y, trans->z);
	scal = scaling(trans->x, trans->y, trans->z);
	sp->trans = mult_matrix(tr, scal);
	free_sub_matrix(tr);
	free_sub_matrix(scal);
	return (sp->trans);
}
