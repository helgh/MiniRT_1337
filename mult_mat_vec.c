/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mult_mat_vec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 18:54:16 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/10/28 19:03:31 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

t_tuple	*mult_mat_vec(double **mat, t_tuple *vec)
{
	t_tuple	*new_vec;

	new_vec = malloc(sizeof(t_tuple));
	new_vec->x = vec->x * mat[0][0];
	new_vec->y = vec->y * mat[1][1];
	new_vec->z = vec->z * mat[2][2];
	new_vec->w = 0;
	return (new_vec);
}
