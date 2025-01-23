/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identity_matrix.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 19:30:08 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/01/23 19:53:01 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

double	**identity_matrix(t_scene *scene)
{
	double	**matrix;
	int	i;

	matrix = ft_malloc(scene, sizeof(double *) * 5, true);
	if (!matrix)
		return (NULL);
	i = -1;
	while (++i < 4)
	{
		matrix[i] = ft_malloc(scene, sizeof(double) * 4, true);
		if (!matrix[i])
			return (NULL);
		matrix[i][i] = 1;
	}
	matrix[i] = NULL;
	return (matrix);
}
