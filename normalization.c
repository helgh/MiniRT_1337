/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalization.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 18:40:52 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/11/01 19:36:04 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

void	normal(t_axis *point)
{
	double	magn;

	magn = magnitude(point);
	point->x = point->x / magn;
	point->y = point->y / magn;
	point->z = point->z / magn;
}