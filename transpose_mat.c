/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transpose_mat.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 23:54:38 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/01/11 19:01:18 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

double	**transpose(double **a)
{
	double	**tr;
	int		i;
	int		s;
	int		size;

	size = count_size(a);
	i = -1;
	tr = malloc(sizeof(double *) * (size + 1));
	if (!tr)
		return (NULL);
	while (++i < size)
	{
		s = -1;
		tr[i] = malloc(sizeof(double) * size);
		while (++s < size)
			tr[i][s] = a[s][i];
	}
	tr[i] = NULL;
	return (tr);
}
