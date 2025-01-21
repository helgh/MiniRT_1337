/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mult_by_scalar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 22:02:04 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/01/19 12:53:51 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

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
