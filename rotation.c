/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 16:10:44 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/01/15 11:54:23 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

static double	**rotate_x(double angle)
{
	double	**rot;

	rot = identity_matrix();
	rot[1][1] = cos(angle);
	rot[1][2] = sin(angle);
	if (rot[1][2] >= EPSILON)
		rot[1][2] *= -1;
	rot[2][1] = sin(angle);
	rot[2][2] = cos(angle);
	return (rot);
}

static double	**rotate_y(double angle)
{
	double	**rot;

	rot = identity_matrix();
	rot[0][0] = cos(angle);
	rot[0][2] = sin(angle);
	rot[2][0] = sin(angle);
	if (rot[2][0] >= EPSILON)
		rot[2][0] *= -1;
	rot[2][2] = cos(angle);
	return (rot);
}
static double	**rotate_z(double angle)
{
	double	**rot;

	rot = identity_matrix();
	rot[1][1] = cos(angle);
	rot[0][0] = cos(angle);
	rot[1][0] = sin(angle);
	rot[0][1] = sin(angle);
	if (rot[0][1] >= EPSILON)
		rot[0][1] *= -1;
	return (rot);
}
double	**rotation(double angle, char axis)
{
	if (axis == 'x')
		return (rotate_x(angle));
	else if (axis == 'y')
		return (rotate_y(angle));
	else if (axis == 'z')
		return (rotate_z(angle));
	return (NULL);
}
