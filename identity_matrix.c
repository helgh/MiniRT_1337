/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identity_matrix.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 15:47:10 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/12/20 16:53:24 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

double	**identity_matrix(void)
{
	double	**matrix;
	int	i;

	matrix = calloc(5, sizeof(double *));
	if (!matrix)
		return (NULL);
	i = -1;
	while (++i < 4)
	{
		matrix[i] = calloc(4, sizeof(double));
		if (!matrix[i])
			return (NULL);
		matrix[i][i] = 1;
	}
	matrix[i] = NULL;
	return (matrix);
}
