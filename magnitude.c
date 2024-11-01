/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   magnitude.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 18:26:51 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/11/01 19:35:15 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

double	magnitude(t_axis *point)
{
	double	magnitude;
	double	x;
	double	y;
	double	z;

	x = point->x;
	y = point->y;
	z = point->z;
	magnitude = pow(x, 2);
	magnitude += pow(y, 2);
	magnitude += pow(z, 2);
	magnitude = sqrt(magnitude);
	return (magnitude);
}
