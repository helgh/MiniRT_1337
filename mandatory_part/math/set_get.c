/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:57:13 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/02/06 17:30:24 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Minirt.h"

t_tuple	vector(double x, double y, double z)
{
	t_tuple	tuple;

	return (tuple.x = x,
		tuple.y = y,
		tuple.z = z,
		tuple.w = 0.0, tuple);
}

t_tuple	point(double x, double y, double z)
{
	t_tuple	tuple;

	return (tuple.x = x,
		tuple.y = y,
		tuple.z = z,
		tuple.w = 1.0, tuple);
}

t_color	color(double r, double g, double b)
{
	t_color	color;

	return (color.r = r,
		color.g = g,
		color.b = b, color);
}
