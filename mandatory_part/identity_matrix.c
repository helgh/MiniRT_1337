/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identity_matrix.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 19:30:08 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/01/27 16:16:36 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

double	**identity_matrix(t_scene *scene)
{
	double	**matrix;
	int	i;
	int	s;

	matrix = malloc(sizeof(double *) * 5);
	if (matrix == NULL)
		return (print_scene_err(scene, F_MALL), NULL);
	i = -1;
	while (++i < 4)
	{
		s = -1;
		matrix[i] = malloc(sizeof(double) * 4);
		if (matrix[i] == NULL)
			return (print_scene_err(scene, F_MALL), NULL);
		while (++s < 4)
		{
			if (i == s)
				matrix[i][s] = 1.0;
			else
				matrix[i][s] = 0.0;
		}
	}
	matrix[i] = NULL;
	return (matrix);
}
