/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 19:53:21 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/01/23 19:56:53 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

double	**translation(t_scene *scene, double x, double y, double z)
{
	double	**tr;

	tr = identity_matrix(scene);
	tr[0][3] = x;
	tr[1][3] = y;
	tr[2][3] = z;
	return (tr);
}

double	**scaling(t_scene *scene, double x, double y, double z)
{
	double	**scaling;

	scaling = identity_matrix(scene);
	scaling[0][0] = x;
	scaling[1][1] = y;
	scaling[2][2] = z;
	return (scaling);
}

