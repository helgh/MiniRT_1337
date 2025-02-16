/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inverse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 20:04:02 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/02/16 19:01:45 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Minirt.h"

double	**inverse(t_scene *scene, double **a)
{
	int		row;
	int		col;
	double	**a2;
	double	**a3;
	double	determinant;

	determinant = det(scene, a);
	if (determinant == 0.0)
		return (NULL);
	a2 = ft_malloc(scene, sizeof(double *) * 5);
	if (!a2)
		return (NULL);
	row = -1;
	while (++row < 4)
	{
		col = -1;
		a2[row] = ft_malloc(scene, sizeof(double) * 4);
		while (++col < 4)
			a2[row][col] = cofactor(scene, a, row, col) / determinant;
	}
	a2[row] = NULL;
	a3 = transpose(scene, a2);
	return (a3);
}
