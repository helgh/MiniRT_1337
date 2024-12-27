/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 17:15:47 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/12/20 17:27:59 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

double	**translation(double x, double y, double z, double w)
{
	double	**tr;

	tr = identity_matrix();
	tr[0][3] = x;
	tr[1][3] = y;
	tr[2][3] = z;
	tr[3][3] = w;
	return (tr);
}
