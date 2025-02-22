/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:45:16 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/02/22 21:20:28 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Minirt.h"

double	**view_transform(t_scene *scene, t_tuple from, t_tuple to, t_tuple up)
{
	t_tuple		forward;
	t_tuple		left;
	t_tuple		true_up;
	t_tmp_heap	*tmp;
	double		**orientation;

	tmp = scene->tmp_heap;
	forward = vector(to.x, to.y, to.z);
	left = cross_product(forward, up);
	true_up = cross_product(left, forward);
	tmp->scal = identity_matrix(scene);
	tmp->scal[0][0] = left.x;
	tmp->scal[0][1] = left.y;
	tmp->scal[0][2] = left.z;
	tmp->scal[1][0] = true_up.x;
	tmp->scal[1][1] = true_up.y;
	tmp->scal[1][2] = true_up.z;
	tmp->scal[2][0] = -forward.x;
	tmp->scal[2][1] = -forward.y;
	tmp->scal[2][2] = -forward.z;
	tmp->trans = translation(scene, -from.x, -from.y, -from.z);
	orientation = mult_matrix(scene, tmp->scal, tmp->trans);
	scene->tmp_heap->trans = free_matrix(tmp->trans);
	scene->tmp_heap->scal = free_matrix(tmp->scal);
	return (orientation);
}
