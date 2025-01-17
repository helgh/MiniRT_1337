/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_at.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 17:52:15 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/01/15 13:47:18 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

t_tuple	normal_at(t_sphere sp, t_tuple point)
{
	t_tuple	obj_vec;
	t_tuple	obj_p;
	t_tuple	world_vec;
	double	**a;
	double	**b;

	a = inverse(sp.trans);
	obj_p = mult_mat_point(a, point);
	obj_vec = op_tuple(obj_p, create_tuple(0, 0, 0, 1), '-', 1);
	b = transpose(a);
	world_vec = mult_mat_point(b, obj_vec);
	world_vec.w = 0;
	free_sub_matrix(a);
	free_sub_matrix(b);
	return (normal(world_vec));
}
