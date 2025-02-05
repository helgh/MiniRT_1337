/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mult_matrix.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 20:00:18 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/02/05 18:17:04 by hael-ghd         ###   ########.fr       */
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

double	**mult_matrix(t_scene *scene, double **a, double **b)
{
	int		i;
	int		s;
	int		size;
	double	**new_mat;

	i = -1;
	size = count_size(a);
	new_mat = malloc(sizeof(double *) * (size + 1));
	if (!new_mat)
		print_scene_err(scene, F_MALL);
	while (++i < size)
	{
		new_mat[i] = malloc(sizeof(double) * size);
		if (!new_mat[i])
			print_scene_err(scene, F_MALL);
	}
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
