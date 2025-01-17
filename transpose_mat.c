/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transpose_mat.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 23:54:38 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/01/15 12:47:06 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

double	**transpose(double **a)
{
	double	**tr;
	int		i;
	int		s;

	i = -1;
	tr = malloc(sizeof(double *) * (5));
	while (++i < 4)
	{
		s = -1;
		tr[i] = malloc(sizeof(double) * 4);
		while (++s < 4)
			tr[i][s] = a[s][i];
	}
	tr[i] = NULL;
	return (tr);
}
