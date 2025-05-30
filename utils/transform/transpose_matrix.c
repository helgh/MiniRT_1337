/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transpose_matrix.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 20:20:29 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/03/05 16:15:50 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../utils.h"

double	**transpose(t_scene *scene, double **a)
{
	double	**tr;
	int		i;
	int		s;

	i = -1;
	tr = ft_malloc(scene, sizeof(double *) * 5);
	while (++i < 4)
	{
		s = -1;
		tr[i] = ft_malloc(scene, sizeof(double) * 4);
		while (++s < 4)
			tr[i][s] = a[s][i];
	}
	tr[i] = NULL;
	return (tr);
}
