/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_vector.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:15:47 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/01/29 17:21:51 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

// count magnitude (lenght) of a vector //

// Normalization is the process of taking an arbitrary vector and converting it into a unit vector //
// turn vector into a unit vector while preserving its direction //
double	magnitude(t_tuple v)
{
	if (v.x == 0.0 && v.y == 0.0 && v.z == 0.0)
		return (-1.0);
	return (sqrt(pow(v.x, 2.0) + pow(v.y, 2.0) + pow(v.z, 2.0)));
}

t_tuple	normal(t_tuple tuple)
{
	double	magn;

	magn = magnitude(tuple);
	return (tuple_scal(tuple, magn, DIV));
}

t_tuple	reflect(t_tuple in, t_tuple normal)
{
	double	n;

	n = 2.0 * dot_product(in, normal);
	return (op_tuple(in, tuple_scal(normal, n, MULT), SUB));
}

double	dot_product(t_tuple vec1, t_tuple vec2)
{
	return ((vec1.x * vec2.x) +
		(vec1.y * vec2.y) +
		(vec1.z * vec2.z));
}

t_tuple	cross_product(t_tuple vec1, t_tuple vec2)
{
	t_tuple	vec3;

	return (vec3.x = (vec1.y * vec2.z) - (vec1.z * vec2.y),
		vec3.y = (vec1.z * vec2.x) - (vec1.x * vec2.z),
		vec3.z = (vec1.x * vec2.y) - (vec1.y * vec2.x),
		vec3.w = 0.0, vec3);
}

