/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transpose_mat.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 23:54:38 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/10/27 23:21:03 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

double	**trans_mat(double **a)
{
	double	**tr;
	int		i;
	int		s;
	int		size;

	size = count_size(a);
	i = -1;
	tr = malloc(sizeof(double *) * (size + 1));
	while (++i < size)
	{
		s = -1;
		tr[i] = malloc(sizeof(double) * size);
		while (++s < size)
			tr[s][i] = a[i][s];
	}
	tr[i] = NULL;
	return (tr);
}
