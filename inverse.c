/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inverse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 15:54:39 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/01/11 19:00:42 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

double	**inverse(double **a)
{
	int		row;
	int		col;
	double	**a2;
	double	**a3;
	double	determinant;

	determinant = det(a);
	if (determinant == 0)
		return (NULL);
	a2 = malloc(sizeof(double *) * count_size(a) + 1);
	if (!a2)
		return (NULL);
	row = -1;
	while (++row < 4)
	{
		col = -1;
		a2[row] = malloc(sizeof(double) * 4);
		while (++col < 4)
			a2[row][col] = cofactor(a, row, col) / determinant;
	}
	a2[row] = NULL;
	a3 = transpose(a2);
	free_sub_matrix(a2);
	return (a3);
}
