/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:45:16 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/03/23 00:06:44 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Minirt_bonus.h"

static t_tuple	check_forward(t_tuple from, t_tuple to)
{
	if (!to.x && !to.y && !to.z)
	{
		to.w = 1;
		return (normal(op_tuple(to, from, SUB)));
	}
	return (to);
}

static t_tuple	check_cross_p(t_tuple forward)
{
	t_tuple	up;
	t_tuple	new_axe;

	new_axe = cross_product(forward, vector(0.0, 1.0, 0.0));
	if (!new_axe.x && !new_axe.y && !new_axe.z)
	{
		up = vector(EPSILON, 1.0, 0.0);
		new_axe = normal(cross_product(forward, up));
	}
	return (new_axe);
}

double	**view_transform(t_scene *scene, t_tuple from, t_tuple to)
{
	t_tuple		forward;
	t_tuple		left;
	t_tuple		true_up;
	t_tmp_heap	*tmp;
	double		**orientation;

	tmp = scene->tmp_heap;
	forward = check_forward(from, to);
	left = check_cross_p(forward);
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
