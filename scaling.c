/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scaling.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 18:45:26 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/11/02 21:18:43 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

double	**scaling(double x, double y, double z, double w)
{
	double	**scaling;
	int		i;
	int		s;

	scaling = malloc(sizeof(double *) * 5);
	i = -1;
	while (++i < 4)
	{
		scaling[i] = malloc(sizeof(double) * 4);
		s = -1;
		while (++s < 4)
			if (i != s)
				scaling[i][s] = 0;
	}
	scaling[0][0] = x;
	scaling[1][1] = y;
	scaling[2][2] = z;
	scaling[3][3] = w;
	scaling[4] = NULL;
	return (scaling);
}
