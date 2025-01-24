/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tuple.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:15:47 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/01/24 13:24:02 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

// count magnitude (lenght) of a vector //

double	magnitude(t_tuple v)
{
	return (sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2)));
}

// Normalization is the process of taking an arbitrary vector and converting it into a unit vector //
// turn vector into a unit vector while preserving its direction //

t_tuple	normal(t_tuple tuple)
{
	t_tuple	new_tuple;
	double	magn;

	magn = magnitude(tuple);
	new_tuple.x = tuple.x / magn;
	new_tuple.y = tuple.y / magn;
	new_tuple.z = tuple.z / magn;
	new_tuple.w = tuple.w;
	return (new_tuple);
}

t_tuple	cross_product(t_tuple vec1, t_tuple vec2)
{
	t_tuple	vec3;

	vec3.x = (vec1.y * vec2.z) - (vec1.z * vec2.y);
	vec3.y = (vec1.z * vec2.x) - (vec1.x * vec2.z);
	vec3.z = (vec1.x * vec2.y) - (vec1.y * vec2.x);
	vec3.w = 0;
	return (vec3);
}


static t_tuple	tuple_by_scalar(t_tuple tuple, double scalar)
{
	t_tuple	new_tuple;

	new_tuple.x = tuple.x * scalar;
	new_tuple.y = tuple.y * scalar;
	new_tuple.z = tuple.z * scalar;
	new_tuple.w = tuple.w * scalar;
	return (new_tuple);
}

t_tuple	op_tuple(t_tuple tuple1, t_tuple tuple2, char operator, double scalar)
{
	t_tuple	new_tuple;

	if (operator == '*')
	{
		new_tuple.x = tuple1.x * tuple2.x;
		new_tuple.y = tuple1.y * tuple2.y;
		new_tuple.z = tuple1.z * tuple2.z;
		return (new_tuple.w = 0, new_tuple);
	}
	else if (operator == '+')
	{
		new_tuple.x = tuple1.x + tuple2.x;
		new_tuple.y = tuple1.y + tuple2.y;
		new_tuple.z = tuple1.z + tuple2.z;
		new_tuple.w = tuple1.w + tuple2.w;
		return (new_tuple);
	}
	else if (operator == 0)
		return (tuple_by_scalar(tuple1, scalar));
	new_tuple.x = tuple1.x - tuple2.x;
	new_tuple.y = tuple1.y - tuple2.y;
	new_tuple.z = tuple1.z - tuple2.z;
	new_tuple.w = tuple1.w - tuple2.w;
	return (new_tuple);
}


t_tuple	create_tuple(double x, double y, double z, double w)
{
	t_tuple	tuple;

	tuple.x = x;
	tuple.y = y;
	tuple.z = z;
	tuple.w = w;
	return (tuple);
}
