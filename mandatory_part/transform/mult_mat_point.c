/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mult_mat_point.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 16:46:43 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/02/07 19:36:44 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Minirt.h"

t_tuple	mult_mat_point(double **mat, t_tuple point)
{
	t_tuple	new_point;

	if (!mat)
		return (point);
	new_point.x = (point.x * mat[0][0]) + \
		(point.y * mat[0][1]) + (point.z * mat[0][2]);
	new_point.x += (point.w * mat[0][3]);
	new_point.y = (point.x * mat[1][0]) + (point.y * mat[1][1]) + \
		(point.z * mat[1][2]);
	new_point.y += (point.w * mat[1][3]);
	new_point.z = (point.x * mat[2][0]) + (point.y * mat[2][1]) + \
		(point.z * mat[2][2]);
	new_point.z += (point.w * mat[2][3]);
	new_point.w = (point.x * mat[3][0]) + (point.y * mat[3][1]) + \
		(point.z * mat[3][2]);
	new_point.w += (point.w * mat[3][3]);
	return (new_point);
}
