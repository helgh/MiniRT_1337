/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mult_matrix.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 19:42:47 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/01/16 15:08:04 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

static double	find_new_value(double **a, double **b, int i, int s)
{
	double	value;
	int		r;
	int		size;

	r = -1;
	value = 0;
	size = count_size(a);
	while (++r < size)
		value += (a[i][r] * b[r][s]);
	return (value);
}

double	**mult_matrix(double **a, double **b)
{
	int		i;
	int		s;
	int		size;
	double	**new_mat;

	i = -1;
	size = count_size(a);
	new_mat = malloc(sizeof(double *) * (size + 1));
	while (++i < size)
		new_mat[i] = malloc(sizeof(double) * size);
	i = -1;
	while (++i < size)
	{
		s = -1;
		while (++s < size)
			new_mat[i][s] = find_new_value(a, b, i, s);
	}
	new_mat[i] = NULL;
	return (new_mat);
}
