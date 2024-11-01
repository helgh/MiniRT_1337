/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_x.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 16:10:44 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/10/31 18:24:36 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

double	**rotate_x(double angle)
{
	double	**rot;
	int		i;

	rot = malloc(sizeof(double *) * 5);
	i = -1;
	while (++i < 4)
	{
		rot[i] = malloc(sizeof(double) * 4);
		bzero(rot[i], sizeof(double) * 4);
	}
	rot[0][0] = 1;
	rot[3][3] = 1;
	rot[1][1] = cos(angle);
	rot[1][2] = -1 * sin(angle);
	rot[2][1] = sin(angle);
	rot[2][2] = cos(angle);
	rot[4] = NULL;
	return (rot);
}

double	**rotate_y(double angle)
{
	double	**rot;
	int		i;

	rot = malloc(sizeof(double *) * 5);
	i = -1;
	while (++i < 4)
	{
		rot[i] = malloc(sizeof(double) * 4);
		bzero(rot[i], sizeof(double) * 4);
	}
	rot[1][1] = 1;
	rot[3][3] = 1;
	rot[0][0] = cos(angle);
	rot[0][2] = sin(angle);
	rot[2][0] = -1 * sin(angle);
	rot[2][2] = cos(angle);
	rot[4] = NULL;
	// printf("-- %f -- %f -- %f -- %f --\n",rot[1][1], rot[1][2], rot[2][1], rot[2][2]);
	return (rot);
}
double	**rotate_z(double angle)
{
	double	**rot;
	int		i;

	rot = malloc(sizeof(double *) * 5);
	i = -1;
	while (++i < 4)
	{
		rot[i] = malloc(sizeof(double) * 4);
		bzero(rot[i], sizeof(double) * 4);
	}
	rot[2][2] = 1;
	rot[3][3] = 1;
	rot[1][1] = cos(angle);
	rot[0][0] = cos(angle);
	rot[1][0] = sin(angle);
	rot[0][1] = -1 * sin(angle);
	rot[4] = NULL;
	// printf("-- %f -- %f -- %f -- %f --\n",rot[1][1], rot[1][2], rot[2][1], rot[2][2]);
	return (rot);
}
