/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 19:54:21 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/02/06 17:31:59 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Minirt.h"

static double	**rotate_x(t_scene *scene, double angle)
{
	double	**rot;

	rot = identity_matrix(scene);
	rot[1][1] = cos(angle);
	rot[1][2] = -sin(angle);
	rot[2][1] = sin(angle);
	rot[2][2] = cos(angle);
	return (rot);
}

static double	**rotate_y(t_scene *scene, double angle)
{
	double	**rot;

	rot = identity_matrix(scene);
	rot[0][0] = cos(angle);
	rot[0][2] = sin(angle);
	rot[2][0] = -sin(angle);
	rot[2][2] = cos(angle);
	return (rot);
}
static double	**rotate_z(t_scene *scene, double angle)
{
	double	**rot;

	rot = identity_matrix(scene);
	rot[1][1] = cos(angle);
	rot[0][0] = cos(angle);
	rot[1][0] = sin(angle);
	rot[0][1] = -sin(angle);
	return (rot);
}

double	**rotation(t_scene *scene, double angle, char axis)
{
	if (axis == ROTATE_X)
		return (rotate_x(scene, angle));
	else if (axis == ROTATE_Y)
		return (rotate_y(scene, angle));
	else if (axis == ROTATE_Z)
		return (rotate_z(scene, angle));
	return (NULL);
}
