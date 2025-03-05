/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rot_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:12:28 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/03/05 16:15:36 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../utils.h"

static double	**get_rot(t_scene *scene, t_tmp_heap *tmp, double beta)
{
	int	i;
	int	j;

	i = -1;
	tmp->rot = identity_matrix(scene);
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
		{
			tmp->trans[i][j] = (1 - cos(beta)) * tmp->trans[i][j];
			tmp->rot[i][j] = tmp->rot[i][j] + tmp->trans[i][j]
				+ tmp->scal[i][j];
		}
	}
	tmp->scal = free_matrix(tmp->scal);
	tmp->trans = free_matrix(tmp->trans);
	return (tmp->rot);
}

double	**_get_trans_rot(t_scene *scene, t_tuple target)
{
	t_tmp_heap	tmp;
	t_tuple		init;
	t_tuple		new_vec;
	double		beta;

	init = vector(0.0, 1.0, 0.0);
	new_vec = normal(cross_product(init, target));
	beta = acos(dot_product(init, target));
	tmp.scal = identity_matrix(scene);
	tmp.scal[0][1] = (-new_vec.z);
	tmp.scal[1][0] = new_vec.z;
	tmp.scal[1][2] = -new_vec.x;
	tmp.scal[2][1] = new_vec.x;
	tmp.scal[0][0] = 0;
	tmp.scal[1][1] = 0;
	tmp.scal[2][2] = 0;
	tmp.scal[3][3] = 0;
	tmp.trans = mult_matrix(scene, tmp.scal, tmp.scal);
	tmp.scal[0][1] = sin(beta) * (-new_vec.z);
	tmp.scal[1][0] = sin(beta) * new_vec.z;
	tmp.scal[1][2] = sin(beta) * -new_vec.x;
	tmp.scal[2][1] = sin(beta) * new_vec.x;
	return (get_rot(scene, &tmp, beta));
}
