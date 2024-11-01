/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shearing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:08:44 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/10/30 20:44:44 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

void	help_shearing(double **sh, t_axis *p1, t_axis *p2, t_axis *p3)
{
	sh[0][1] = p1->y;
	sh[0][2] = p1->z;
	sh[1][0] = p2->x;
	sh[1][2] = p2->z;
	sh[2][0] = p3->x;
	sh[2][1] = p3->y;
}

double	**shearing(t_axis *p1, t_axis *p2, t_axis *p3)
{
	double	**sh;
	int		i;
	int		s;

	i = -1;
	sh = malloc(sizeof(double *) * 5);
	while (++i < 4)
	{
		s = -1;
		sh[i] = malloc(sizeof(double) * 4);
		bzero(sh[i], 4);
		while (++s < 4)
			if (i == s)
				sh[i][s] = 1;
	}
	help_shearing(sh, p1, p2, p3);
	return (sh);
}
