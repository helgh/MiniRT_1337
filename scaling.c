/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scaling.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 18:45:26 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/12/20 17:46:26 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

double	**scaling(double x, double y, double z, double w)
{
	double	**scaling;

	scaling = identity_matrix();
	scaling[0][0] = x;
	scaling[1][1] = y;
	scaling[2][2] = z;
	scaling[3][3] = w;
	return (scaling);
}
