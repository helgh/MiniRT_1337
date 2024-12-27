/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_x.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 16:10:44 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/12/20 19:08:27 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

double	**rotate_x(double angle)
{
	double	**rot;

	rot = identity_matrix();
	rot[1][1] = cos(angle);
	rot[1][2] = -1 * sin(angle);
	rot[2][1] = sin(angle);
	rot[2][2] = cos(angle);
	return (rot);
}

double	**rotate_y(double angle)
{
	double	**rot;

	rot = identity_matrix();
	rot[0][0] = cos(angle);
	rot[0][2] = sin(angle);
	rot[2][0] = -1 * sin(angle);
	rot[2][2] = cos(angle);
	return (rot);
}
double	**rotate_z(double angle)
{
	double	**rot;

	rot = identity_matrix();
	rot[1][1] = cos(angle);
	rot[0][0] = cos(angle);
	rot[1][0] = sin(angle);
	rot[0][1] = -1 * sin(angle);
	return (rot);
}
